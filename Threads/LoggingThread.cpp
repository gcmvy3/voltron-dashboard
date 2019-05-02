/*!
   \class LoggingThread
   \inherits QObject
   \brief The LoggingThread class is a custom class which manages packets being sent to the Voltron Logging process.

   \ingroup voltron
   \ingroup vlogging

   A single LoggingThread object is used to send command packets to the Voltron Logging process.
   These packets tell the Logging process to start or stop logging certain sets of data from the Core process.

   \sa LoggingWidget, LoggingManager
*/

#include "LoggingThread.h"
#include "CommunicationManager.h"

/*!
 * Constructs a LoggingThread object for management of Logging packets.
 *
 * Objects from this class must be moved into a \l QThread.
 */
LoggingThread::LoggingThread()
{
    qRegisterMetaType<LoggingControlPacket>("LoggingPacket");
}

/*!
 * Destroys the object.
 */
LoggingThread::~LoggingThread()
{

}

// Starts the thread
/*!
 * Executed when the thread the associated object was moved to signals that it has started running.
 *
 * Upon execution, a UDP socket is set up for handling Logging packets and is added to the group of sockets being used by the Dashboard.
 * This socket is used to send packets to the Logging process.
 */
void LoggingThread::start()
{
    udpSocket = new QUdpSocket();
    udpSocket->bind(QHostAddress::AnyIPv4, LOGGING_CONTROL_PORT, QUdpSocket::ShareAddress);

    udpSocket->joinMulticastGroup(QHostAddress(CommunicationManager::getUDPAddress()), CommunicationManager::getLoopbackInterface());
}

/*!
 * Converts the packet \a packet into a QByteArray and broadcasts it to the Logging process through the corresponding UDP socket.
 */
void LoggingThread::broadcastPacket(LoggingControlPacket packet)
{
    QByteArray datagram = QByteArray::fromRawData((char *)&packet, sizeof(packet));
    udpSocket->writeDatagram(datagram.data(), datagram.size(), CommunicationManager::getUDPAddress(), LOGGING_CONTROL_PORT);
}

