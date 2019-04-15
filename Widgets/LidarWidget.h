#ifndef LIDARWIDGET_H
#define LIDARWIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QThread>
#include <QLabel>
#include <QVBoxLayout>
#include "CommunicationManager.h"
#include "Threads/Packets.h"
#include "Widgets/LidarRenderer.h"

class LidarWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LidarWidget(QWidget *parent = nullptr);

    QLabel* title;
    LidarRenderer* renderer;

protected:
    void showEvent( QShowEvent* event) override;

signals:

public slots:
    void onStartReading();
    void onStopReading();
    void newPacket(LidarPacket packet);
};

#endif // LIDARWIDGET_H
