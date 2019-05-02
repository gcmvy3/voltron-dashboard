#ifndef STEREOWIDGET_H
#define STEREOWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QThread>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>

#include "CommunicationManager.h"
#include "Threads/Packets.h"
#include "Widgets/StereoMemory.h"

class StereoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit StereoWidget(QWidget *parent = nullptr);

    QLabel* title;
    StereoMemory* display;
    QComboBox* typeSelector;

protected:

signals:

public slots:
    void onTypeChanged();
};

#endif // STEREOWIDGET_H
