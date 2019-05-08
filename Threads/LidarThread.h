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
    ~LidarThread();
    LIDARPacket* latestPacket;

signals:
    void finished();
    void error(QString error);
    void newPacket(LIDARPacket packet);

public slots:
    void start();
    void readPendingDatagrams();

private:
    QUdpSocket* udpSocket;
    void processDatagram(QByteArray datagram);
};

#endif // LIDARTHREAD_H
