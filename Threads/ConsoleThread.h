#ifndef CONSOLETHREAD_H
#define CONSOLETHREAD_H

#include <QObject>
#include <QtNetwork/QUdpSocket>
#include <QNetworkInterface>

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

signals:
    void finished();
    void error(QString error);
    void newPacket(ConsolePacket packet);

private:

    QUdpSocket* udpSocket;

    ConsolePacket* latestPacket;

    void processDatagram(QByteArray datagram);
};

#endif // CONSOLETHREAD_H
