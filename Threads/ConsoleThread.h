#ifndef CONSOLETHREAD_H
#define CONSOLETHREAD_H

#include <iostream>
#include <fstream>
#include <QObject>

#include "Threads/Packets.h"

class ConsoleThread : public QObject
{
    Q_OBJECT
public:
    ConsoleThread();
    ~ConsoleThread();

public slots:
    void start();

signals:
    void finished();
    void error(QString error);
    void newPacket(ConsolePacket packet);

private:

    static const int PIPE_CLOSED_ERROR = 1;
    static const int NO_PACKET_ERROR = 2;

    std::ifstream consolePipe;

    ConsolePacket latestPacket;

    int openPipe();

    ConsolePacket readPacket();
};

#endif // CONSOLETHREAD_H
