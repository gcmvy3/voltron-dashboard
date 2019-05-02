/*!
   \class ConsoleThread
   \inherits QObject
   \brief The ConsoleThread class is a custom class which manages packets for the Console Widget.

   \ingroup voltron
   \ingroup vconsole

   A single ConsoleThread object is used to read all packets containing output and error messages from the Voltron Core process.
   The data from these packets are extracted and sent to the corresponding \l ConsoleWidget object(s).

   \sa ConsoleWidget
*/


#include "ConsoleThread.h"
#include "CommunicationManager.h"

using namespace std;

// Constructor
/*!
 * Constructs a ConsoleThread object for management of Console packets.
 *
 * Objects from this class must be moved into a \l QThread.
 */
ConsoleThread::ConsoleThread()
{
    qRegisterMetaType<DebugPacket>("DebugPacket");
}

// Destructor
/*!
 * Destroys the object.
 */
ConsoleThread::~ConsoleThread()
{

}

// Starts the thread
/*!
 * Executed when the thread the associated object was moved to signals that it has started running.
 *
 * Upon execution, a UDP socket is set up for handling Console packets and is added to the group of sockets being used to communicate with the Voltron Core process.
 * Additionally, a connection is set up so that any packets which can be read from this socket are read.
 */
void ConsoleThread::start()
{
    udpSocket = new QUdpSocket();
    udpSocket->bind(QHostAddress::AnyIPv4, DEBUG_PORT, QUdpSocket::ShareAddress);

    udpSocket->joinMulticastGroup(QHostAddress(CommunicationManager::getUDPAddress()), CommunicationManager::getLoopbackInterface());

    connect(udpSocket, SIGNAL(readyRead()),
                this, SLOT(readPendingDatagrams()));
}

/*!
 * Executed when the UDP socket associated with this class signals that there is data to be read from the Voltron Core process.
 *
 * Upon execution, the available data is read into a QByteArray from the UDP socket and passed to the \l {ConsoleThread::} {processDatagram(QByteArray datagram)} function.
 */
void ConsoleThread::readPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams())
    {
            QByteArray datagram;
            datagram.resize(udpSocket->pendingDatagramSize());
            QHostAddress sender;
            quint16 senderPort;

            udpSocket->readDatagram(datagram.data(), datagram.size(),
                                    &sender, &senderPort);

            ConsoleThread::processDatagram(datagram);
     }
}

/*!
 * Creates a DebugPacket struct containing the data extracted from \a datagram and emits a signal containing this struct to be used by \l ConsoleWidget objects.
 */
void ConsoleThread::processDatagram(QByteArray datagram)
{
    DebugPacket* consolePacket = (DebugPacket*)datagram.data();
    ConsoleThread::latestPacket = consolePacket;

    emit newPacket(*consolePacket);
}

/*!
 * Creates a DebugPacket struct containing the provided \a message and its length and emits a signal containing this struct to be used by \l ConsoleWidget objects.
 */
void ConsoleThread::injectMessage(QString message)
{
    DebugPacket* consolePacket = new DebugPacket();
    strcpy(consolePacket->str, message.toUtf8().constData());
    consolePacket->strLength = message.length();
    emit newPacket(*consolePacket);
}
