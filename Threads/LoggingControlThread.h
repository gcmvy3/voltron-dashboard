#ifndef LOGGINGCONTROLTHREAD_H
#define LOGGINGCONTROLTHREAD_H

#include <QObject>
#include <QtNetwork/QUdpSocket>
#include <QNetworkInterface>

#include "Threads/Packets.h"

class LoggingControlThread : public QObject
{
    Q_OBJECT
public:
    LoggingControlThread();
    ~LoggingControlThread();

signals:
    void finished();
    void error(QString error);

public slots:
    void start();
    void broadcastPacket(LoggingControlPacket packet);

private:
    QUdpSocket* udpSocket;
};

#endif // LOGGINGCONTROLTHREAD_H
