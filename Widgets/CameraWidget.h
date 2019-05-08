#ifndef CAMERAWIDGET_H
#define CAMERAWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QThread>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>

#include "CommunicationManager.h"
#include "Threads/Packets.h"
#include "Widgets/CameraRenderer.h"

class CameraWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CameraWidget(QWidget *parent = nullptr);

    QLabel* title;
    CameraRenderer* display;
    QComboBox* typeSelector;

protected:

signals:

public slots:
    void onTypeChanged();
};

#endif // CAMERAWIDGET_H
