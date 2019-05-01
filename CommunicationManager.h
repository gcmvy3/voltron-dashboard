#ifndef COMMUNICATIONMANAGER_H
#define COMMUNICATIONMANAGER_H

#include <QObject>
#include "Threads/BatteryThread.h"
#include "Threads/ConsoleThread.h"
#include "Threads/LidarThread.h"
#include "Threads/CANThread.h"
#include "Threads/StereoThread.h"
#include "Threads/LoggingControlThread.h"
#include <QThread>

class CommunicationManager : QObject
{
    Q_OBJECT

public:
    static void init();

    static BatteryThread* batteryThread;
    static ConsoleThread* consoleThread;
    static LidarThread* lidarThread;
    static CANThread* canThread;
    static StereoThread* stereoThread;
    static LoggingControlThread* loggingControlThread;

    static QHostAddress getUDPAddress(){return QHostAddress(MULTICAST_GROUP);}

    static QNetworkInterface getLoopbackInterface();

private:
    static bool loopbackFound;
    static QNetworkInterface loopbackInterface;

signals:

public slots:
    static void printToConsole(QString);
};

#endif // COMMUNICATIONMANAGER_H
