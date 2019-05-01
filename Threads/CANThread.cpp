#include "CANThread.h"
#include "CommunicationManager.h"
#include "CANCodeManager.h"

// Constructor
CANThread::CANThread()
{
    qRegisterMetaType<CANDataPacket>("CANDataPacket");
    qRegisterMetaType<CANControlPacket>("CANControlPacket");
    qRegisterMetaType<QVector<CANCode*>>("QVector<CANCode*>>");

    QObject::connect(CANCodeManager::getInstance() , &CANCodeManager::newCodesLoaded, this, &CANThread::onNewCANCodesLoaded);
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

void CANThread::onNewCANCodesLoaded(QVector<CANCode*> codes)
{
    for(int i = 0; i < codes.size(); i++)
    {
        CANCode* code = codes.at(i);

        CANControlPacket request = CANControlPacket();

        request.id = code->id;
        request.sender = code->senderID;
        broadcastCANRequest(request);
    }
}

void CANThread::broadcastCANRequest(CANControlPacket packet)
{
    QByteArray datagram = QByteArray::fromRawData((char *)&packet, sizeof(packet));
    controlSocket->writeDatagram(datagram.data(), datagram.size(), CommunicationManager::getUDPAddress(), CAN_CONTROL_PORT);
}

QByteArray CANThread::serializeRequestPacket(CANControlPacket packet)
{
    QByteArray byteArray;

    QDataStream stream(&byteArray, QIODevice::WriteOnly);
    stream << packet.id << packet.sender;

    return byteArray;
}
