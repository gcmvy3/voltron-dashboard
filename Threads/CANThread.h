#ifndef CANTHREAD_H
#define CANTHREAD_H

#include <QObject>
#include <QtNetwork/QUdpSocket>
#include <QNetworkInterface>
#include <iostream>
#include <QDataStream>

#include "Threads/Packets.h"

class CANThread : public QObject
{
    Q_OBJECT

public:
    CANThread();
    ~CANThread();

public slots:
    void start();
    void readPendingDatagrams();
    void broadcastPacket(CANPacket packet);

signals:
    void finished();
    void error(QString error);
    void newPacket(CANPacket packet);

private:
    QUdpSocket* udpSocket;
    CANPacket* latestPacket;
    void processDatagram(QByteArray datagram);
    QByteArray serializePacket(CANPacket packet);
};

#endif // CANTHREAD_H
