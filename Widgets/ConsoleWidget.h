#ifndef CONSOLEWIDGET_H
#define CONSOLEWIDGET_H

#include <QWidget>
#include <QTextBrowser>
#include <QPushButton>
#include <QThread>
#include <QDateTime>
#include "CommunicationManager.h"
#include "Threads/Packets.h"

class ConsoleWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ConsoleWidget(QWidget *parent = nullptr);

    QTextBrowser *console;
    QPushButton *readButton;

    ConsoleThread *consoleThread;

protected:
    void showEvent( QShowEvent* event) override;
    void hideEvent( QHideEvent* event) override;

signals:

public slots:
    void onStartReading();
    void onStopReading();
    void newPacket(DebugPacket packet);
    void errorString(QString error);
};

#endif // CONSOLEWIDGET_H
