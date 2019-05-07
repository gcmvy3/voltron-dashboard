#ifndef BATTERYWIDGET_H
#define BATTERYWIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QThread>
#include "CommunicationManager.h"
#include "DashboardUtils.h"
#include "Threads/Packets.h"

class BatteryWidget : public QWidget
{   
    Q_OBJECT
public:
    explicit BatteryWidget(QWidget *parent = nullptr);

    const int NUM_CELLS = 20;

    int widgetIndex = -1;

    QTableWidget *table;

protected:
    void showEvent( QShowEvent* event) override;
    void hideEvent( QHideEvent* event) override;

signals:

public slots:
    void onStartReading();
    void onStopReading();
    void onPacket(BatteryPacket packet);
    void errorString(QString error);
};

#endif // BATTERYWIDGET_H
