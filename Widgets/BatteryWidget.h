#ifndef BATTERYWIDGET_H
#define BATTERYWIDGET_H

#include <QWidget>
#include <QTableWidget>
#include "Threads/Packets.h"

class BatteryWidget : public QTableWidget
{
    Q_OBJECT
public:
    explicit BatteryWidget(QWidget *parent = nullptr);

    const int NUM_CELLS = 20;

signals:

public slots:
    void newPacket(BatteryPacket packet);
};

#endif // BATTERYWIDGET_H
