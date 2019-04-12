#include "LidarThread.h"
#include "CommunicationManager.h"

LidarThread::LidarThread(QObject *parent) : QObject(parent)
{
    qRegisterMetaType<LidarPacket>("LidarPacket");
}

// Starts the thread
void LidarThread::start()
{
    udpSocket = new QUdpSocket();
    udpSocket->bind(QHostAddress::AnyIPv4, LIDAR_PORT, QUdpSocket::ShareAddress);

    udpSocket->joinMulticastGroup(QHostAddress(CommunicationManager::getUDPAddress()), CommunicationManager::getLoopbackInterface());

    connect(udpSocket, SIGNAL(readyRead()),
                this, SLOT(readPendingDatagrams()));
}

void LidarThread::readPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams())
    {
            QByteArray datagram;
            datagram.resize(udpSocket->pendingDatagramSize());
            QHostAddress sender;
            quint16 senderPort;

            udpSocket->readDatagram(datagram.data(), datagram.size(),
                                    &sender, &senderPort);

            LidarThread::processDatagram(datagram);
     }
}


void LidarThread::processDatagram(QByteArray datagram)
{
    LidarPacket* lidarPacket = (LidarPacket*)datagram.data();
    LidarThread::latestPacket = lidarPacket;
    emit newPacket(*lidarPacket);
}
