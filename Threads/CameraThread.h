#ifndef CAMERATHREAD_H
#define CAMERATHREAD_H

#include <QObject>
#include <QtNetwork/QUdpSocket>
#include <QNetworkInterface>

#include "Threads/Packets.h"

class CameraThread : public QObject
{
    Q_OBJECT
public:
    explicit CameraThread(QObject *parent = nullptr);
    CameraPacket* latestPacket;

signals:
    void finished();
    void error(QString error);
    void newPacket(CameraPacket packet);

public slots:
    void start();
    void readPendingDatagrams();

private:
    QUdpSocket* udpSocket;
    void processDatagram(QByteArray datagram);
};

#endif // CameraThread_H
