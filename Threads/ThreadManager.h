#ifndef THREADMANAGER_H
#define THREADMANAGER_H

#include <QObject>
#include <Threads/BatteryThread.h>

class ThreadManager : QObject
{
public:
    ThreadManager();

    static BatteryThread *batteryThread;

public slots:
    void startBatteryThread();

signals:
    void finished();
    void error(QString error);
    void newPacket(BatteryPacket packet);

private:
};

#endif // THREADMANAGER_H
