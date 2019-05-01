#include "LoggingControlThread.h"
#include "CommunicationManager.h"

LoggingControlThread::LoggingControlThread()
{
    qRegisterMetaType<LoggingControlPacket>("LoggingControlPacket");
}

LoggingControlThread::~LoggingControlThread()
{

}

// Starts the thread
void LoggingControlThread::start()
{
    udpSocket = new QUdpSocket();
    udpSocket->bind(QHostAddress::AnyIPv4, LOGGING_CONTROL_PORT, QUdpSocket::ShareAddress);

    udpSocket->joinMulticastGroup(QHostAddress(CommunicationManager::getUDPAddress()), CommunicationManager::getLoopbackInterface());
}

void LoggingControlThread::broadcastPacket(LoggingControlPacket packet)
{
    QByteArray datagram = QByteArray::fromRawData((char *)&packet, sizeof(packet));
    udpSocket->writeDatagram(datagram.data(), datagram.size(), CommunicationManager::getUDPAddress(), LOGGING_CONTROL_PORT);
}
