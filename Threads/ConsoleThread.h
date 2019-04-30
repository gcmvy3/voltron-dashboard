#ifndef CONSOLETHREAD_H
#define CONSOLETHREAD_H

#include <QObject>
#include <QtNetwork/QUdpSocket>
#include <QNetworkInterface>
#include <iostream>

#include "Threads/Packets.h"

class ConsoleThread : public QObject
{
    Q_OBJECT
public:
    ConsoleThread();
    ~ConsoleThread();

public slots:
    void start();
    void readPendingDatagrams();
    void injectMessage(QString message);

signals:
    void finished();
    void error(QString error);
    void newPacket(DebugPacket packet);

private:

    QUdpSocket* udpSocket;

    DebugPacket* latestPacket;

    void processDatagram(QByteArray datagram);
};

#endif // CONSOLETHREAD_H
