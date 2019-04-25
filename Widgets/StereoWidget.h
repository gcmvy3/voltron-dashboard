#ifndef STEREOWIDGET_H
#define STEREOWIDGET_H

#include <QWidget>
#include <QThread>
#include "CommunicationManager.h"
#include "Threads/Packets.h"

class StereoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit StereoWidget(QWidget *parent = nullptr);

protected:
    void showEvent( QShowEvent* event) override;

signals:

public slots:
    void onStartReading();
    void onStopReading();
    void newPacket(StereoPacket packet);
    void errorString(QString error);
};

#endif // STEREOWIDGET_H
