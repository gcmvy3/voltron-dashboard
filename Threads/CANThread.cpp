#include "CANThread.h"
#include "CommunicationManager.h"

// Constructor
CANThread::CANThread()
{
    qRegisterMetaType<CANPacket>("CANPacket");
}

// Destructor
CANThread::~CANThread()
{

}

// Starts the thread
void CANThread::start()
{
    udpSocket = new QUdpSocket();
    udpSocket->bind(QHostAddress::AnyIPv4, CAN_PORT, QUdpSocket::ShareAddress);

    udpSocket->joinMulticastGroup(QHostAddress(CommunicationManager::getUDPAddress()), CommunicationManager::getLoopbackInterface());

    connect(udpSocket, SIGNAL(readyRead()),
                this, SLOT(readPendingDatagrams()));
}

void CANThread::readPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams())
    {
            QByteArray datagram;
            datagram.resize(udpSocket->pendingDatagramSize());
            QHostAddress sender;
            quint16 senderPort;

            udpSocket->readDatagram(datagram.data(), datagram.size(),
                                    &sender, &senderPort);

            CANThread::processDatagram(datagram);
     }
}

void CANThread::processDatagram(QByteArray datagram)
{
    CANPacket* canPacket = (CANPacket*)datagram.data();
    CANThread::latestPacket = canPacket;
    emit newPacket(*canPacket);
}

void CANThread::broadcastCANRequest(CANRequestPacket packet)
{
    QByteArray datagram = serializeRequestPacket(packet);
    udpSocket->writeDatagram(datagram.data(), datagram.size(), CommunicationManager::getUDPAddress(), CAN_PORT);
}

QByteArray CANThread::serializeRequestPacket(CANRequestPacket packet)
{
    QByteArray byteArray;

    QDataStream stream(&byteArray, QIODevice::WriteOnly);
    stream << packet.id << packet.sender;

    return byteArray;
}
