#ifndef STEREOTHREAD_H
#define STEREOTHREAD_H

#include <QObject>
#include <QtNetwork/QUdpSocket>
#include <QNetworkInterface>

#include "Threads/Packets.h"

class StereoThread : public QObject
{
    Q_OBJECT
public:
    StereoThread();
    ~StereoThread();

public slots:
    void start();
    void readPendingDatagrams();

signals:
    void finished();
    void error(QString error);
    void newPacket(StereoPacket packet);

private:

    QUdpSocket* udpSocket;

    StereoPacket* latestPacket;

    void processDatagram(QByteArray datagram);
};

#endif // STEREOTHREAD_H
