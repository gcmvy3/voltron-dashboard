#include "LoggingThread.h"
#include "CommunicationManager.h"

LoggingThread::LoggingThread()
{
    qRegisterMetaType<LoggingControlPacket>("LoggingPacket");
}

LoggingThread::~LoggingThread()
{

}

// Starts the thread
void LoggingThread::start()
{
    udpSocket = new QUdpSocket();
    udpSocket->bind(QHostAddress::AnyIPv4, LOGGING_CONTROL_PORT, QUdpSocket::ShareAddress);

    udpSocket->joinMulticastGroup(QHostAddress(CommunicationManager::getUDPAddress()), CommunicationManager::getLoopbackInterface());
}

void LoggingThread::broadcastPacket(LoggingControlPacket packet)
{
    QByteArray datagram = QByteArray::fromRawData((char *)&packet, sizeof(packet));
    udpSocket->writeDatagram(datagram.data(), datagram.size(), CommunicationManager::getUDPAddress(), LOGGING_CONTROL_PORT);
}

