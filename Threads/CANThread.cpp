/*!
   \class CANThread
   \inherits QObject
   \brief The CANThread class is a custom class which receives CAN data from the Voltron Core program.

   \ingroup voltron
   \ingroup vCAN

   A single CANThread object is used to read all packets containing CAN code data from the Voltron Core process.
   The thread first broadcasts a CANControlPacket for each CAN code it wants to subscribe to. The core program receives these
   control packets and begins to broadcast the corresponding CAN code value in real time. These arrive as CANDataPackets,
   which are received by the CANThread object.

   \sa CANWidget, CANCode, CANCodeManager
*/

#include "CANThread.h"
#include "CommunicationManager.h"
#include "CANCodeManager.h"

// Constructor
/*!
 * Constructs a CANThread object for management of CAN packets.
 *
 * Objects from this class must be moved into a \l QThread.
 */
CANThread::CANThread()
{
    qRegisterMetaType<CANDataPacket>("CANDataPacket");
    qRegisterMetaType<CANControlPacket>("CANControlPacket");
    qRegisterMetaType<QVector<CANCode*>>("QVector<CANCode*>>");

    QObject::connect(CANCodeManager::getInstance() , &CANCodeManager::newCodesLoaded, this, &CANThread::onNewCANCodesLoaded);
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
    // Initialize data socket
    dataSocket = new QUdpSocket(this);
    dataSocket->bind(QHostAddress::AnyIPv4, CAN_DATA_PORT, QUdpSocket::ShareAddress);

    dataSocket->joinMulticastGroup(QHostAddress(CommunicationManager::getUDPAddress()), CommunicationManager::getLoopbackInterface());

    connect(dataSocket, SIGNAL(readyRead()),
                this, SLOT(readPendingDatagrams()));

    connect(CANCodeManager::getInstance(), &CANCodeManager::codesCleared, this, &CANThread::onCodesCleared);

    // Initialize control socket
    controlSocket = new QUdpSocket(this);
    controlSocket->bind(QHostAddress(QStringLiteral("127.0.0.1")), CAN_CONTROL_PORT, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
    controlSocket->setMulticastInterface(CommunicationManager::getLoopbackInterface());
}

/*!
 * Executed when the UDP socket associated with this class signals that there is data to be read from the Voltron Core process.
 *
 * Upon execution, the available data is read into a QByteArray from the UDP socket and passed to the \l {CANThread::} {processDatagram(QByteArray datagram)} function.
 */
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

/*!
 * Creates a CANPacket struct containing the data extracted from \a datagram and emits a signal containing this struct to be used by ...
 */
void CANThread::processDatagram(QByteArray datagram)
{
    CANDataPacket* canPacket = (CANDataPacket*)datagram.data();
    CANThread::latestPacket = canPacket;

    QString data = "";
    for(int i = 0; i < 8; i++)
    {
        data.append(QString::number(canPacket->data[i]));
    }

    emit newPacket(*canPacket);
}

/*!
 * A convenience function for requesting several CANControlPackets at once. Is called when a new CAN code file is loaded by the dashboard.
 */
void CANThread::onNewCANCodesLoaded(QVector<CANCode*> codes)
{
    for(int i = 0; i < codes.size(); i++)
    {
        CANCode* code = codes.at(i);

        CANControlPacket request = CANControlPacket();

        request.pktId = code->id;
        request.sender = code->senderID;
        broadcastCANRequest(request);
    }
}

/*!
 * Converts the packet \a packet into a QByteArray and broadcasts it to the Core process through the corresponding UDP socket.
 */
void CANThread::broadcastCANRequest(CANControlPacket packet)
{
    QByteArray datagram = QByteArray::fromRawData((char *)&packet, sizeof(packet));
    controlSocket->writeDatagram(datagram.data(), datagram.size(), QHostAddress(QStringLiteral(MULTICAST_GROUP)), CAN_CONTROL_PORT);
}

/*!
 * Tells the core program to stop sending all CAN data.
 * It's a good idea to delay requests immediately after unsubscribing, to ensure that the packet has time to arrive.
 */
void CANThread::onCodesCleared()
{
    CANControlPacket request = CANControlPacket();
    request.pktId = -1;
    request.sender = -1;
    broadcastCANRequest(request);

    // Wait a little bit to allow the core program to clear
    QThread::msleep(10);
}

