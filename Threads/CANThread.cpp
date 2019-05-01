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
    // Initialize data socket
    dataSocket = new QUdpSocket();
    dataSocket->bind(QHostAddress::AnyIPv4, CAN_DATA_PORT, QUdpSocket::ShareAddress);

    dataSocket->joinMulticastGroup(QHostAddress(CommunicationManager::getUDPAddress()), CommunicationManager::getLoopbackInterface());

    connect(dataSocket, SIGNAL(readyRead()),
                this, SLOT(readPendingDatagrams()));

    // Initialize control socket
    controlSocket = new QUdpSocket();
    controlSocket->bind(QHostAddress::AnyIPv4, CAN_CONTROL_PORT, QUdpSocket::ShareAddress);

    controlSocket->joinMulticastGroup(QHostAddress(CommunicationManager::getUDPAddress()), CommunicationManager::getLoopbackInterface());

    CANControlPacket testPacket;
    testPacket.id = 0;

    bool success;
    int senderID = QString("0x0CFF6600").toInt(&success, 16);
    if(!success)
    {
        qDebug() << "ERROR: Could not convert hex string to int";
    }

    qDebug() << "Sender ID: " << senderID;
    testPacket.sender = senderID;
    broadcastCANRequest(testPacket);

    CANControlPacket testPacket2;
    testPacket2.id = 1;

    bool success2;
    int senderID2 = QString("0x08FF07EF").toInt(&success2, 16);
    if(!success2)
    {
        qDebug() << "ERROR: Could not convert hex string to int";
    }

    qDebug() << "Sender ID: " << senderID2;
    testPacket2.sender = senderID2;
    broadcastCANRequest(testPacket2);
}

void CANThread::readPendingDatagrams()
{
    while (dataSocket->hasPendingDatagrams())
    {
            QByteArray datagram;
            datagram.resize(dataSocket->pendingDatagramSize());
            QHostAddress sender;
            quint16 senderPort;

            dataSocket->readDatagram(datagram.data(), datagram.size(),
                                    &sender, &senderPort);

            CANThread::processDatagram(datagram);
     }
}

void CANThread::processDatagram(QByteArray datagram)
{
    CANDataPacket* canPacket = (CANDataPacket*)datagram.data();
    CANThread::latestPacket = canPacket;

    QString data = "";
    for(int i = 0; i < 8; i++)
    {
        data.append(QString::number(canPacket->data[i]));
    }

    qDebug() << "Received CAN data:\nSender ID: " << canPacket->sender << "\nCode ID: " << canPacket->id << "\nData: " << data;

    emit newPacket(*canPacket);
}

void CANThread::broadcastCANRequest(CANControlPacket packet)
{
    QByteArray datagram = QByteArray::fromRawData((char *)&packet, sizeof(packet));
    controlSocket->writeDatagram(datagram.data(), datagram.size(), CommunicationManager::getUDPAddress(), CAN_CONTROL_PORT);
    qDebug("Broadcast CAN request");
}

QByteArray CANThread::serializeRequestPacket(CANControlPacket packet)
{
    QByteArray byteArray;

    QDataStream stream(&byteArray, QIODevice::WriteOnly);
    stream << packet.id << packet.sender;

    return byteArray;
}
