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
    explicit StereoThread(QObject *parent = nullptr);

signals:
    void finished();
    void error(QString error);
    void newPacket(StereoPacket packet);

public slots:
    void start();
    void readPendingDatagrams();

private:

    QUdpSocket* udpSocket;

    StereoPacket* latestPacket;

    void processDatagram(QByteArray datagram);
};

#endif // STEREOTHREAD_H
