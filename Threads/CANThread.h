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
    void broadcastCANRequest(CANControlPacket request);

signals:
    void finished();
    void error(QString error);
    void newPacket(CANDataPacket packet);

private:
    QUdpSocket* udpSocket;
    CANDataPacket* latestPacket;
    void processDatagram(QByteArray datagram);
    QByteArray serializeRequestPacket(CANControlPacket packet);
};

#endif // CANTHREAD_H
