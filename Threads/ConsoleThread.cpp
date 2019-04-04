#include <iostream>
#include <fstream>

#include "ConsoleThread.h"
#include "Packets.h"

using namespace std;

// Constructor
ConsoleThread::ConsoleThread()
{
    qRegisterMetaType<ConsolePacket>("ConsolePacket");
}

// Destructor
ConsoleThread::~ConsoleThread()
{

}

// Starts the thread
void ConsoleThread::start()
{
    // Try to open the console pipe
    if(openPipe() == 0)
    {
        // Read packets continually until the thread is stopped
        while(1)
        {
            try
            {
               ConsolePacket bufferPacket = readPacket();
               latestPacket = bufferPacket;
               emit newPacket(latestPacket);
            }
            catch(int exception)
            {
                if(exception == PIPE_CLOSED_ERROR)
                {
                    emit error("Error: console pipe closed unexpectedly");
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
        emit error("Error: Could not open console pipe");
    }

    emit finished();
}

// Tries to open the console pipe created by the core program
int ConsoleThread::openPipe()
{
    consolePipe.open(CONSOLE_PIPE_NAME, ifstream::in);

    if(consolePipe.fail())
    {
        return 1;
    }

    return 0;
}

// Tries to read a packet from the console pipe
// Throws an error if the pipe is closed or if there are no packets to read
ConsolePacket ConsoleThread::readPacket()
{
    struct ConsolePacket packet;
    QString actualMsg;
    struct DebugPacket dpacket;

    if(consolePipe.is_open())
    {
        if(consolePipe.peek() == EOF)
        {
            throw NO_PACKET_ERROR;
        }
        else
        {
            consolePipe.read((char*)&dpacket, sizeof(struct DebugPacket));

            char msg[dpacket.strLength];
            consolePipe.read((char*)&msg, dpacket.strLength);
            packet.msg = QString(msg);
            return packet;
        }
    }
    else
    {
        throw PIPE_CLOSED_ERROR;
    }
}




