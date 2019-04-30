#include "CANThread.h"
#include "CommunicationManager.h"

// Constructor
CANThread::CANThread()
{
    qRegisterMetaType<CANDataPacket>("CANDataPacket");
    qRegisterMetaType<CANControlPacket>("CANControlPacket");
}

// Destructor
CANThread::~CANThread()
{

}

// Starts the thread
void CANThread::start()
{
    udpSocket = new QUdpSocket();
    udpSocket->bind(QHostAddress::AnyIPv4, CAN_DATA_PORT, QUdpSocket::ShareAddress);

    udpSocket->joinMulticastGroup(QHostAddress(CommunicationManager::getUDPAddress()), CommunicationManager::getLoopbackInterface());

    connect(udpSocket, SIGNAL(readyRead()),
                this, SLOT(readPendingDatagrams()));

    CANControlPacket testPacket;
    testPacket.id << 0;

    bool success;
    int senderID = QString("0CFF6600").toInt(&success, 16);

    testPacket.sender << senderID;
    broadcastCANRequest(testPacket);
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
    CANDataPacket* canPacket = (CANDataPacket*)datagram.data();
    CANThread::latestPacket = canPacket;

    qDebug() << "Received CAN data:\nSender ID: " << canPacket->sender << "\nCode ID: " << canPacket->id << "\nData: " << canPacket->data;

    emit newPacket(*canPacket);
}

void CANThread::broadcastCANRequest(CANControlPacket packet)
{
    QByteArray datagram = serializeRequestPacket(packet);
    udpSocket->writeDatagram(datagram.data(), datagram.size(), CommunicationManager::getUDPAddress(), CAN_CONTROL_PORT);
}

QByteArray CANThread::serializeRequestPacket(CANControlPacket packet)
{
    QByteArray byteArray;

    QDataStream stream(&byteArray, QIODevice::WriteOnly);
    stream << packet.id << packet.sender;

    return byteArray;
}
