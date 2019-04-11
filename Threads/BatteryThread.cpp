#include <iostream>
#include <fstream>

#include "BatteryThread.h"
#include "Packets.h"

using namespace std;

const QString udpAddress = "224.0.0.155";

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

    QNetworkInterface loopbackInterface;

    // Get loopback interface from list of interfaces
    QList<QNetworkInterface> ifaces = QNetworkInterface::allInterfaces();
    for(int i=0; i < ifaces.size(); i++)
    {
        QNetworkInterface interface = ifaces[i];
        if((bool)(interface.flags() & QNetworkInterface::IsLoopBack))
        {
            loopbackInterface = interface;
            break;
        }
    }

    udpSocket->joinMulticastGroup(QHostAddress(udpAddress), loopbackInterface);

    connect(udpSocket, SIGNAL(readyRead()),
                this, SLOT(readPendingDatagrams()));
}

void BatteryThread::readPendingDatagrams()
{
    qDebug("Starting to listen for datagrams");

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




