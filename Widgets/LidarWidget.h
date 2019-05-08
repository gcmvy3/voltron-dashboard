#ifndef LIDARWIDGET_H
#define LIDARWIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QThread>
#include <QLabel>
#include <QVBoxLayout>
#include <QSlider>
#include "CommunicationManager.h"
#include "Threads/Packets.h"
#include "Widgets/LidarRenderer.h"

class LidarWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LidarWidget(QWidget *parent = nullptr);

    QLabel* title;
    QSlider* zoomSlider;
    LidarRenderer* renderer;

protected:

signals:

public slots:
};

#endif // LIDARWIDGET_H
