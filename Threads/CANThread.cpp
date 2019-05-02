/*!
   \class CANThread
   \inherits QObject
   \brief The CANThread class is a custom class which ....

   \ingroup voltron
   \ingroup vCAN

   A single CANThread object is used to read all packets containing CAN code data from the Voltron Core process.
   The data from these packets are extracted ...

   \sa ...
*/

#include "CANThread.h"
#include "CommunicationManager.h"

// Constructor
/*!
 * Constructs a CANThread object for management of CAN packets.
 *
 * Objects from this class must be moved into a \l QThread.
 */
CANThread::CANThread()
{
    qRegisterMetaType<CANPacket>("CANPacket");
}

// Destructor
/*!
 * Destroys the object.
 */
CANThread::~CANThread()
{

}

// Starts the thread
/*!
 * Executed when the thread the associated object was moved to signals that it has started running.
 *
 * Upon execution, a UDP socket is set up for handling CAN packets and is added to the group of sockets being used to communicate with the Voltron Core process.
 * Additionally, a connection is set up so that any packets which can be read from this socket are read.
 */
void CANThread::start()
{
    udpSocket = new QUdpSocket();
    udpSocket->bind(QHostAddress::AnyIPv4, CAN_PORT, QUdpSocket::ShareAddress);

    udpSocket->joinMulticastGroup(QHostAddress(CommunicationManager::getUDPAddress()), CommunicationManager::getLoopbackInterface());

    connect(udpSocket, SIGNAL(readyRead()),
                this, SLOT(readPendingDatagrams()));
}

/*!
 * Executed when the UDP socket associated with this class signals that there is data to be read from the Voltron Core process.
 *
 * Upon execution, the available data is read into a QByteArray from the UDP socket and passed to the \l {CANThread::} {processDatagram(QByteArray datagram)} function.
 */
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

/*!
 * Creates a CANPacket struct containing the data extracted from \a datagram and emits a signal containing this struct to be used by ...
 */
void CANThread::processDatagram(QByteArray datagram)
{
    CANPacket* canPacket = (CANPacket*)datagram.data();
    CANThread::latestPacket = canPacket;
    emit newPacket(*canPacket);
}

/*!
 * ...
 */
void CANThread::broadcastPacket(CANPacket packet)
{
    QByteArray datagram = serializePacket(packet);
    udpSocket->writeDatagram(datagram.data(), datagram.size(), CommunicationManager::getUDPAddress(), CAN_PORT);
}

/*!
 * ...
 */
QByteArray CANThread::serializePacket(CANPacket packet)
{
    QByteArray byteArray;

    QDataStream stream(&byteArray, QIODevice::WriteOnly);
    stream << packet.id << packet.sender << packet.bitStart << packet.bitEnd;

    return byteArray;
}
