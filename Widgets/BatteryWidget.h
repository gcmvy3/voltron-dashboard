#ifndef BATTERYWIDGET_H
#define BATTERYWIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QThread>
#include "CommunicationManager.h"
#include "Threads/Packets.h"

class BatteryWidget : public QWidget
{   
    Q_OBJECT
public:
    explicit BatteryWidget(QWidget *parent = nullptr);

    const int NUM_CELLS = 20;

    QTableWidget *table;

protected:
    void showEvent( QShowEvent* event) override;

signals:

public slots:
    void onStartReading();
    void onStopReading();
    void newPacket(BatteryPacket packet);
    void errorString(QString error);
};

#endif // BATTERYWIDGET_H
