/*!
   \class StereoThread
   \inherits QObject
   \brief The StereoThread class is a custom class which manages packets for the Stereo Widget.

   \ingroup voltron
   \ingroup vstereo

   A single StereoThread object is used to read all packets containing indicators of new data from the Voltron Core process.
   The data from these packets are extracted and sent to the corresponding \l StereoMemory object(s).

   \sa StereoMemory, StereoWidget
*/

#include <iostream>
#include <fstream>

#include "StereoThread.h"
#include "Packets.h"
#include "CommunicationManager.h"

using namespace std;

// Constructor
/*!
 * Constructs a StereoThread object for management of Stereo packets.
 *
 * Objects from this class must be moved into a \l QThread.
 */
StereoThread::StereoThread(QObject *parent) : QObject(parent)
{
    qRegisterMetaType<StereoPacket>("StereoPacket");
}

// Starts the thread
/*!
 * Executed when the thread the associated object was moved to signals that it has started running.
 *
 * Upon execution, a UDP socket is set up for handling Lidar packets and is added to the group of sockets being used to communicate with the Voltron Core process.
 * Additionally, a connection is set up so that any packets which can be read from this socket are read.
 */
void StereoThread::start()
{
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::AnyIPv4, CAMERA_PORT, QUdpSocket::ShareAddress);

    udpSocket->joinMulticastGroup(QHostAddress(CommunicationManager::getUDPAddress()), CommunicationManager::getLoopbackInterface());

    connect(udpSocket, SIGNAL(readyRead()),
                this, SLOT(readPendingDatagrams()));
}

/*!
 * Executed when the UDP socket associated with this class signals that there is data to be read from the Voltron Core process.
 *
 * Upon execution, the available data is read into a QByteArray from the UDP socket and passed to the \l {StereoThread::} {processDatagram(QByteArray datagram)} function.
 */
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

/*!
 * Creates a StereoPacket struct containing the data extracted from \a datagram and emits a signal containing this struct to be used by \l StereoMemory objects.
 */
void StereoThread::processDatagram(QByteArray datagram)
{
    StereoPacket* stereoPacket = (StereoPacket*)datagram.data();
    StereoThread::latestPacket = stereoPacket;
    emit newPacket(*stereoPacket);
}
