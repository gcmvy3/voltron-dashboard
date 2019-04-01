#ifndef BATTERYWIDGET_H
#define BATTERYWIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QThread>
#include <QHeaderView>
#include "Threads/Packets.h"
#include "Threads/BatteryThread.h"

class BatteryWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BatteryWidget(QWidget *parent = nullptr);

    const int NUM_CELLS = 20;

    QPushButton *toggleButton;
    QTableWidget *table;

signals:

public slots:
    void onButtonToggled(bool buttonChecked);
    void onStartReading();
    void onStopReading();
    void newPacket(BatteryPacket packet);

private:
    BatteryThread *batteryThread;

};

#endif // BATTERYWIDGET_H
