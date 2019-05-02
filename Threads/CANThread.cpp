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

    qDebug() << "Received CAN data:\nSender ID: " << canPacket->sender << "\nCode ID: " << canPacket->id << "\nData: " << data;

    emit newPacket(*canPacket);
}

/*!
 * ...
 */
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

/*!
 * ...
 */
void CANThread::broadcastCANRequest(CANControlPacket packet)
{
    QByteArray datagram = QByteArray::fromRawData((char *)&packet, sizeof(packet));
    controlSocket->writeDatagram(datagram.data(), datagram.size(), CommunicationManager::getUDPAddress(), CAN_CONTROL_PORT);
}

/*!
 * ...
 */
QByteArray CANThread::serializeRequestPacket(CANControlPacket packet)
{
    QByteArray byteArray;

    QDataStream stream(&byteArray, QIODevice::WriteOnly);
    stream << packet.id << packet.sender;

    return byteArray;
}
