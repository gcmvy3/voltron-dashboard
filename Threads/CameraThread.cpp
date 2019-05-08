/*!
   \class CameraThread
   \inherits QObject
   \brief The CameraThread class is a custom class which manages packets for the Camera Widget.

   \ingroup voltron
   \ingroup vstereo

   A single CameraThread object is used to read all packets containing indicators of new data from the Voltron Core process.
   The data from these packets are extracted and sent to the corresponding \l CameraRenderer object(s).

   \sa CameraRenderer, CameraWidget
*/

#include <iostream>
#include <fstream>

#include "CameraThread.h"
#include "Packets.h"
#include "CommunicationManager.h"

using namespace std;

// Constructor
/*!
 * Constructs a CameraThread object for management of Stereo packets.
 *
 * Objects from this class must be moved into a \l QThread.
 */
CameraThread::CameraThread(QObject *parent) : QObject(parent)
{
    qRegisterMetaType<CameraPacket>("CameraPacket");
}

// Starts the thread
/*!
 * Executed when the thread the associated object was moved to signals that it has started running.
 *
 * Upon execution, a UDP socket is set up for handling Lidar packets and is added to the group of sockets being used to communicate with the Voltron Core process.
 * Additionally, a connection is set up so that any packets which can be read from this socket are read.
 */
void CameraThread::start()
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
 * Upon execution, the available data is read into a QByteArray from the UDP socket and passed to the \l {CameraThread::} {processDatagram(QByteArray datagram)} function.
 */
void CameraThread::readPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams())
    {
            QByteArray datagram;
            datagram.resize(udpSocket->pendingDatagramSize());
            QHostAddress sender;
            quint16 senderPort;

            udpSocket->readDatagram(datagram.data(), datagram.size(),
                                    &sender, &senderPort);

            CameraThread::processDatagram(datagram);
     }
}

/*!
 * Creates a StereoPacket struct containing the data extracted from \a datagram and emits a signal containing this struct to be used by \l StereoMemory objects.
 */
void CameraThread::processDatagram(QByteArray datagram)
{
    CameraPacket* stereoPacket = (CameraPacket*)datagram.data();
    CameraThread::latestPacket = stereoPacket;
    emit newPacket(*stereoPacket);
}
