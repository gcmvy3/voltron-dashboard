#include <iostream>
#include <fstream>

#include "StereoThread.h"
#include "Packets.h"
#include "CommunicationManager.h"

using namespace std;

// Constructor
StereoThread::StereoThread(QObject *parent) : QObject(parent)
{
    qRegisterMetaType<StereoPacket>("StereoPacket");
}

// Starts the thread
void StereoThread::start()
{
    udpSocket = new QUdpSocket();
    udpSocket->bind(QHostAddress::AnyIPv4, STEREO_PORT, QUdpSocket::ShareAddress);

    udpSocket->joinMulticastGroup(QHostAddress(CommunicationManager::getUDPAddress()), CommunicationManager::getLoopbackInterface());

    connect(udpSocket, SIGNAL(readyRead()),
                this, SLOT(readPendingDatagrams()));
}

void StereoThread::readPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams())
    {
            QByteArray datagram;
            datagram.resize(udpSocket->pendingDatagramSize());
            QHostAddress sender;
            quint16 senderPort;

            udpSocket->readDatagram(datagram.data(), datagram.size(),
                                    &sender, &senderPort);

            StereoThread::processDatagram(datagram);
     }
}


void StereoThread::processDatagram(QByteArray datagram)
{
    StereoPacket* stereoPacket = (StereoPacket*)datagram.data();
    StereoThread::latestPacket = stereoPacket;
    emit newPacket(*stereoPacket);
}
