/*!
   \class BatteryThread
   \inherits QObject
   \brief The BatteryThread class is a custom class which manages packets for the Battery Widget.

   \ingroup voltron
   \ingroup vbattery

   A single BatteryThread object is used to read all packets containing battery data from the Voltron Core process.
   The data from these packets are extracted and sent to the corresponding \l BatteryWidget object(s).

   \note While this and the \l BatteryWidget classes are fully implemented, the Voltron Core process, at present, does not send true battery data.

   \sa BatteryWidget
*/


#include "BatteryThread.h"
#include "CommunicationManager.h"

using namespace std;

// Constructor
/*!
 * Constructs a BatteryThread object for management of Battery packets.
 *
 * Objects from this class must be moved into a \l QThread.
 */
BatteryThread::BatteryThread()
{
    qRegisterMetaType<BatteryPacket>("BatteryPacket");
}

// Destructor
/*!
 * Destroys the object.
 */
BatteryThread::~BatteryThread()
{

}

// Starts the thread
/*!
 * Executed when the thread the associated object was moved to signals that it has started running.
 *
 * Upon execution, a UDP socket is set up for handling Battery packets and is added to the group of sockets being used to communicate with the Voltron Core process.
 * Additionally, a connection is set up so that any packets which can be read from this socket are read.
 */
void BatteryThread::start()
{
    udpSocket = new QUdpSocket();
    udpSocket->bind(QHostAddress::AnyIPv4, BATTERY_PORT, QUdpSocket::ShareAddress);

    udpSocket->joinMulticastGroup(QHostAddress(CommunicationManager::getUDPAddress()), CommunicationManager::getLoopbackInterface());

    connect(udpSocket, SIGNAL(readyRead()),
                this, SLOT(readPendingDatagrams()));
}

/*!
 * Executed when the UDP socket associated with this class signals that there is data to be read from the Voltron Core process.
 *
 * Upon execution, the available data is read into a QByteArray from the UDP socket and passed to the \l {BatteryThread::} {processDatagram(QByteArray datagram)} function.
 */
void BatteryThread::readPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams())
    {
            QByteArray datagram;
            datagram.resize(udpSocket->pendingDatagramSize());
            QHostAddress sender;
            quint16 senderPort;

            udpSocket->readDatagram(datagram.data(), datagram.size(),
                                    &sender, &senderPort);

            BatteryThread::processDatagram(datagram);
     }
}

/*!
 * Creates a BatteryPacket struct containing the data extracted from \a datagram and emits a signal containing this struct to be used by \l BatteryWidget objects.
 */
void BatteryThread::processDatagram(QByteArray datagram)
{
    BatteryPacket* batteryPacket = (BatteryPacket*)datagram.data();
    BatteryThread::latestPacket = batteryPacket;
    emit newPacket(*batteryPacket);
}
