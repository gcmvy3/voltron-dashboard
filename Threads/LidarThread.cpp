/*!
   \class LidarThread
   \inherits QObject
   \brief The LidarThread class is a custom class which manages packets for the Lidar Widget.

   \ingroup voltron
   \ingroup vlidar

   A single LidarThread object is used to read all packets containing indicators of new data from the Voltron Core process.
   The data from these packets are extracted and sent to the corresponding \l LidarRenderer object(s).

   \sa LidarRenderer, LidarWidget
*/

#include "LidarThread.h"
#include "CommunicationManager.h"


/*!
 * Constructs a LidarThread object for management of Lidar packets.
 *
 * Objects from this class must be moved into a \l QThread.
 */
LidarThread::LidarThread(QObject *parent) : QObject(parent)
{
    qRegisterMetaType<LIDARPacket>("LIDARPacket");
}

LidarThread::~LidarThread()
{

}

// Starts the thread
/*!
 * Executed when the thread the associated object was moved to signals that it has started running.
 *
 * Upon execution, a UDP socket is set up for handling Lidar packets and is added to the group of sockets being used to communicate with the Voltron Core process.
 * Additionally, a connection is set up so that any packets which can be read from this socket are read.
 */
void LidarThread::start()
{
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::AnyIPv4, LIDAR_PORT, QUdpSocket::ShareAddress);

    udpSocket->joinMulticastGroup(QHostAddress(CommunicationManager::getUDPAddress()), CommunicationManager::getLoopbackInterface());

    connect(udpSocket, SIGNAL(readyRead()),
                this, SLOT(readPendingDatagrams()));
}

/*!
 * Executed when the UDP socket associated with this class signals that there is data to be read from the Voltron Core process.
 *
 * Upon execution, the available data is read into a QByteArray from the UDP socket and passed to the \l {LidarThread::} {processDatagram(QByteArray datagram)} function.
 */
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

/*!
 * Creates a LidarPacket struct containing the data extracted from \a datagram and emits a signal containing this struct to be used by \l LidarRenderer objects.
 */
void LidarThread::processDatagram(QByteArray datagram)
{
    LIDARPacket* lidarPacket = (LIDARPacket*)datagram.data();
    LidarThread::latestPacket = lidarPacket;
    emit newPacket(*lidarPacket);
}
