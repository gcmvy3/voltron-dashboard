#ifndef LOGGINGWIDGET_H
#define LOGGINGWIDGET_H

#include <QWidget>
#include <QPushButton>
#include "DashboardUtils.h"
#include "LoggingManager.h"

class LoggingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LoggingWidget(QWidget *parent = nullptr);

    void showEvent( QShowEvent* event) override;

protected:
    int initialized = false;
    int widgetIndex;
    QPushButton* startDriveButton;
    QPushButton* endDriveButton;
    QPushButton* canRecordButton;
    QPushButton* lidarRecordButton;
    QPushButton* cameraRecordButton;
    QPushButton* gpsRecordButton;

private:
    void initialize();
    void updateButtonStatus();

signals:

public slots:
    void onStartDriveButtonPressed();
    void onEndDriveButtonPressed();
    void onCANRecordButtonPressed();
    void onLidarRecordButtonPressed();
    void onCameraRecordButtonPressed();
    void onGPSRecordButtonPressed();
};

#endif // LOGGINGWIDGET_H
