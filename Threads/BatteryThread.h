#ifndef BATTERYTHREAD_H
#define BATTERYTHREAD_H

#include <iostream>
#include <fstream>
#include <QObject>

#include "Threads/Packets.h"

class BatteryThread : public QObject
{
    Q_OBJECT
public:
    BatteryThread();
    ~BatteryThread();

public slots:
    void start();

signals:
    void finished();
    void error(QString error);
    void newPacket(BatteryPacket packet);

private:

    static const int PIPE_CLOSED_ERROR = 1;
    static const int NO_PACKET_ERROR = 2;

    std::ifstream batteryPipe;

    BatteryPacket latestPacket;

    int openPipe();

    BatteryPacket readPacket();
};

#endif // BATTERYTHREAD_H
