#ifndef LOGGINGCONTROLTHREAD_H
#define LOGGINGCONTROLTHREAD_H

#include <QObject>
#include <QtNetwork/QUdpSocket>
#include <QNetworkInterface>

#include "Threads/Packets.h"

class LoggingThread : public QObject
{
    Q_OBJECT
public:
    LoggingThread();
    ~LoggingThread();

signals:
    void finished();
    void error(QString error);

public slots:
    void start();
    void broadcastPacket(LoggingControlPacket packet);

private:
    QUdpSocket* udpSocket;
};

#endif // LOGGINGTHREAD_H
