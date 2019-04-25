#ifndef LIDARTHREAD_H
#define LIDARTHREAD_H

#include <QObject>
#include <QtNetwork/QUdpSocket>
#include <QNetworkInterface>

#include "Threads/Packets.h"


class LidarThread : public QObject
{
    Q_OBJECT
public:
    explicit LidarThread(QObject *parent = nullptr);

signals:
    void finished();
    void error(QString error);
    void newPacket(LidarPacket packet);

public slots:
    void start();
    void readPendingDatagrams();

private:

    QUdpSocket* udpSocket;

    LidarPacket* latestPacket;

    void processDatagram(QByteArray datagram);
};

#endif // LIDARTHREAD_H
