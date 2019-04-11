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

}

// Tries to open the console pipe created by the core program
int ConsoleThread::openPipe()
{
    return 0;
}

// Tries to read a packet from the console pipe
// Throws an error if the pipe is closed or if there are no packets to read
ConsolePacket ConsoleThread::readPacket()
{
    struct ConsolePacket dpacket;
    return dpacket;
}




