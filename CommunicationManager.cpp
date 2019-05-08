/*!
   \class CommunicationManager
   \inherits QWidget
   \brief The CommunicationManager class is a custom class which manages all the \l QThreads and thread objects being used to communicate with the Voltron Core process.

   \ingroup voltron

   This class instantiates the various thread objects handling the different packets being sent by the Voltron Core process and moves each to its own \l QThread.
   Connections are established to enable communication between the thread objects and the \l QThreads they have been moved to, and each \l QThread is started.

   \sa QThread
*/

#include "CommunicationManager.h"

BatteryThread* CommunicationManager::batteryThread;
ConsoleThread* CommunicationManager::consoleThread;
LidarThread* CommunicationManager::lidarThread;
CANThread* CommunicationManager::canThread;
StereoThread* CommunicationManager::stereoThread;
LoggingThread* CommunicationManager::loggingThread;

bool CommunicationManager::loopbackFound = false;
QNetworkInterface CommunicationManager::loopbackInterface;


/*!
 * Instantiates the various thread objects handling the different packets being sent by the Voltron Core process and moves each to its own \l QThread.
 * Connections are established to enable communication between the thread objects and the \l QThreads they have been moved to, and each \l QThread is started.
 * Connections are also established between the CommunicationManager and each thread object so that errors from these objects can be displayed by the dashboard.
 */
void CommunicationManager::init()
{
    // Init and start battery thread
    QThread* batteryQThread = new QThread;
    batteryThread = new BatteryThread();
    batteryThread->moveToThread(batteryQThread);

    // Connect the required signals for a QThread
    QObject::connect(batteryThread, &BatteryThread::error, &CommunicationManager::printToConsole);
    connect(batteryQThread, SIGNAL(started()), batteryThread, SLOT(start()));
    connect(batteryThread, SIGNAL(finished()), batteryQThread, SLOT(quit()));
    connect(batteryThread, SIGNAL(finished()), batteryThread, SLOT(deleteLater()));
    connect(batteryQThread, SIGNAL(finished()), batteryQThread, SLOT(deleteLater()));

    batteryQThread->start();


    // Init and start console thread
    QThread* consoleQThread = new QThread;
    CommunicationManager::consoleThread = new ConsoleThread();
    consoleThread->moveToThread(consoleQThread);

    // Connect the required signals for a QThread
    QObject::connect(consoleThread, &ConsoleThread::error, &CommunicationManager::printToConsole);
    connect(consoleQThread, SIGNAL(started()), consoleThread, SLOT(start()));
    connect(consoleThread, SIGNAL(finished()), consoleQThread, SLOT(quit()));
    connect(consoleThread, SIGNAL(finished()), consoleThread, SLOT(deleteLater()));
    connect(consoleQThread, SIGNAL(finished()), consoleQThread, SLOT(deleteLater()));

    consoleQThread->start();


    // Init and start lidar thread
    QThread* lidarQThread = new QThread;
    CommunicationManager::lidarThread = new LidarThread();
    lidarThread->moveToThread(lidarQThread);

    // Connect the required signals for a QThread
    QObject::connect(lidarThread, &LidarThread::error, &CommunicationManager::printToConsole);
    connect(lidarQThread, SIGNAL(started()), lidarThread, SLOT(start()));
    connect(lidarThread, SIGNAL(finished()), lidarQThread, SLOT(quit()));
    connect(lidarThread, SIGNAL(finished()), lidarThread, SLOT(deleteLater()));
    connect(lidarQThread, SIGNAL(finished()), lidarQThread, SLOT(deleteLater()));

    lidarQThread->start();

    // Init and start CAN thread
    QThread* CANQThread = new QThread;
    canThread = new CANThread();
    canThread->moveToThread(CANQThread);

    // Connect the required signals for a QThread
    QObject::connect(canThread, &CANThread::error, &CommunicationManager::printToConsole);
    connect(CANQThread, SIGNAL(started()), canThread, SLOT(start()));
    connect(canThread, SIGNAL(finished()), CANQThread, SLOT(quit()));
    connect(canThread, SIGNAL(finished()), canThread, SLOT(deleteLater()));
    connect(CANQThread, SIGNAL(finished()), CANQThread, SLOT(deleteLater()));

    CANQThread->start();

    // Init and start stereo thread
    QThread* stereoQThread = new QThread;
    CommunicationManager::stereoThread = new StereoThread();
    stereoThread->moveToThread(stereoQThread);

    // Connect the required signals for a QThread
    QObject::connect(stereoThread, &StereoThread::error, &CommunicationManager::printToConsole);
    connect(stereoQThread, SIGNAL(started()), stereoThread, SLOT(start()));
    connect(stereoThread, SIGNAL(finished()), stereoQThread, SLOT(quit()));
    connect(stereoThread, SIGNAL(finished()), stereoThread, SLOT(deleteLater()));
    connect(stereoQThread, SIGNAL(finished()), stereoQThread, SLOT(deleteLater()));

    stereoQThread->start();

    // Init and start logging  thread
    QThread* loggingQThread = new QThread;
    CommunicationManager::loggingThread = new LoggingThread();
    loggingThread->moveToThread(loggingQThread);

    // Connect the required signals for a QThread
    QObject::connect(loggingThread, &LoggingThread::error, &CommunicationManager::printToConsole);
    connect(loggingQThread, SIGNAL(started()), loggingThread, SLOT(start()));
    connect(loggingThread, SIGNAL(finished()), loggingQThread, SLOT(quit()));
    connect(loggingThread, SIGNAL(finished()), loggingThread, SLOT(deleteLater()));
    connect(loggingQThread, SIGNAL(finished()), loggingQThread, SLOT(deleteLater()));

    loggingQThread->start();
}

/*!
 * Used to find the loopback network interface. This interface is required for communication with the Voltron Core program. This function is cross-platform and helps ensure the correct interface is used.
 */
QNetworkInterface CommunicationManager::getLoopbackInterface()
{
    if(CommunicationManager::loopbackFound)
    {
        return CommunicationManager::loopbackInterface;
    }
    else
    {
        // Get loopback interface from list of interfaces
        QList<QNetworkInterface> ifaces = QNetworkInterface::allInterfaces();
        for(int i=0; i < ifaces.size(); i++)
        {
            QNetworkInterface interface = ifaces.at(i);
            if((bool)(interface.flags() & QNetworkInterface::IsLoopBack))
            {
                CommunicationManager::loopbackFound = true;
                return interface;
            }
        }

        throw "ERROR: No network loopback interface found";
    }
}

/*!
 * Has the consoleThread object emit a packet with \a error as its message, so that it is displayed by any \l ConsoleWidget objects.
 */
void CommunicationManager::printToConsole(QString error)
{
    consoleThread->injectMessage(error);
}
