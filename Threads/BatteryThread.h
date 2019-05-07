#ifndef BATTERYTHREAD_H
#define BATTERYTHREAD_H

#include <QObject>
#include <QtNetwork/QUdpSocket>
#include <QNetworkInterface>

#include "Threads/Packets.h"

class BatteryThread : public QObject
{
    Q_OBJECT
public:
    explicit BatteryThread(QObject *parent = nullptr);
    ~BatteryThread();
    BatteryPacket* latestPacket;

public slots:
    void start();
    void readPendingDatagrams();

signals:
    void finished();
    void error(QString error);
    void newPacket(BatteryPacket packet);

private:
    QUdpSocket* udpSocket;
    void processDatagram(QByteArray datagram);
};

#endif // BATTERYTHREAD_H
