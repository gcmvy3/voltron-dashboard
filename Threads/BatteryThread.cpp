#include <iostream>
#include <fstream>

#include "BatteryThread.h"
#include "Packets.h"

using namespace std;

// Constructor
BatteryThread::BatteryThread()
{
    qRegisterMetaType<BatteryPacket>("BatteryPacket");
}

// Destructor
BatteryThread::~BatteryThread()
{

}

// Starts the thread
void BatteryThread::start()
{
    // Try to open the battery pipe
    if(openPipe() == 0)
    {
        // Read packets continually until the thread is stopped
        while(1)
        {
            try
            {
               BatteryPacket bufferPacket = readPacket();
               latestPacket = bufferPacket;
               emit newPacket(latestPacket);
            }
            catch(int exception)
            {
                if(exception == PIPE_CLOSED_ERROR)
                {
                    emit error("Error: battery pipe closed unexpectedly");
                }
                else if(exception == NO_PACKET_ERROR)
                {
                    // Not a fatal error, so just keep trying to read packets
                }
            }
        }
    }
    else
    {
        emit error("Error: Could not open battery pipe");
    }

    emit finished();
}

// Tries to open the battery pipe created by the core program
int BatteryThread::openPipe()
{
    batteryPipe.open(BATTERY_PIPE_NAME, ifstream::in);

    if(batteryPipe.fail())
    {
        return 1;
    }

    return 0;
}

// Tries to read a packet from the battery pipe
// Throws an error if the pipe is closed or if there are no packets to read
BatteryPacket BatteryThread::readPacket()
{
    struct BatteryPacket packet;

    if(batteryPipe.is_open())
    {
        if(batteryPipe.peek() == EOF)
        {
            throw NO_PACKET_ERROR;
        }
        else
        {
            batteryPipe.read((char*)&packet, sizeof(struct BatteryPacket));
            return packet;
        }
    }
    else
    {
        throw PIPE_CLOSED_ERROR;
    }
}




