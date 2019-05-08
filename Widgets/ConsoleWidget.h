#ifndef CONSOLEWIDGET_H
#define CONSOLEWIDGET_H

#include <QWidget>
#include <QTextBrowser>
#include <QThread>
#include <QDateTime>
#include <QEvent>
#include "CommunicationManager.h"
#include "DashboardUtils.h"
#include "Threads/Packets.h"

class ConsoleWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ConsoleWidget(QWidget *parent = nullptr);

    int widgetIndex = -1;

    QTextBrowser *console;

protected:
    bool event(QEvent *event) override;

signals:

public slots:
    void onStartReading();
    void onStopReading();
    void onPacket(DebugPacket packet);
    void errorString(QString error);
};

#endif // CONSOLEWIDGET_H
