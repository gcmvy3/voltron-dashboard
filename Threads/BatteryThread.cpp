#include <iostream>
#include <fstream>

#include "BatteryThread.h"
#include "Packets.h"
#include "CommunicationManager.h"

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
    udpSocket = new QUdpSocket();
    udpSocket->bind(QHostAddress::AnyIPv4, BATTERY_PORT, QUdpSocket::ShareAddress);

    udpSocket->joinMulticastGroup(QHostAddress(CommunicationManager::getUDPAddress()), CommunicationManager::getLoopbackInterface());

    connect(udpSocket, SIGNAL(readyRead()),
                this, SLOT(readPendingDatagrams()));
}

void BatteryThread::readPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams())
    {
            QByteArray datagram;
            datagram.resize(udpSocket->pendingDatagramSize());
            QHostAddress sender;
            quint16 senderPort;

            udpSocket->readDatagram(datagram.data(), datagram.size(),
                                    &sender, &senderPort);

            BatteryThread::processDatagram(datagram);
     }
}


void BatteryThread::processDatagram(QByteArray datagram)
{
    BatteryPacket* batteryPacket = (BatteryPacket*)datagram.data();
    BatteryThread::latestPacket = batteryPacket;
    emit newPacket(*batteryPacket);
}
