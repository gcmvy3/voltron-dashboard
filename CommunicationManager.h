#ifndef COMMUNICATIONMANAGER_H
#define COMMUNICATIONMANAGER_H

#include <QObject>
#include "Threads/BatteryThread.h"
#include "Threads/ConsoleThread.h"
#include "Threads/LidarThread.h"
#include <QThread>

class CommunicationManager : QObject
{
    Q_OBJECT

public:
    static void init();

    static BatteryThread* batteryThread;
    static ConsoleThread* consoleThread;
    static LidarThread* lidarThread;

    static QHostAddress getUDPAddress(){return QHostAddress("224.0.0.155");}

    static QNetworkInterface getLoopbackInterface();

private:
    static bool loopbackFound;
    static QNetworkInterface loopbackInterface;

signals:

public slots:
    static void printError(QString);
};

#endif // COMMUNICATIONMANAGER_H
