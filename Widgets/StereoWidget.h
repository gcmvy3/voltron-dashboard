#ifndef STEREOWIDGET_H
#define STEREOWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QThread>
#include <QVBoxLayout>

#include "CommunicationManager.h"
#include "Threads/Packets.h"
#include "Widgets/StereoRenderer.h"

class StereoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit StereoWidget(QWidget *parent = nullptr);

    QLabel* title;
    QLabel* display;

protected:
    void showEvent( QShowEvent* event) override;
    void hideEvent( QHideEvent* event) override;

signals:

public slots:
    void onStartReading();
    void onStopReading();
    void newPacket(StereoPacket packet); //Not sure if needed
};

#endif // STEREOWIDGET_H
