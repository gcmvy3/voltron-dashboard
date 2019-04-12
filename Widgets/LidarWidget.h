#ifndef LIDARWIDGET_H
#define LIDARWIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QThread>
#include "CommunicationManager.h"
#include "Threads/Packets.h"

class LidarWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LidarWidget(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // LIDARWIDGET_H
