#ifndef CONSOLEWIDGET_H
#define CONSOLEWIDGET_H

#include <QWidget>
#include <QTextBrowser>
#include <QPushButton>
#include <QThread>
#include "Threads/ConsoleThread.h"
#include "Threads/Packets.h"

class ConsoleWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ConsoleWidget(QWidget *parent = nullptr);

    QTextBrowser *console;
    QPushButton *readButton;

    ConsoleThread *consoleThread;

signals:

public slots:
    void onStartReading();
    void onStopReading();
    void newPacket(ConsolePacket packet);
    void errorString(QString error);
};

#endif // CONSOLEWIDGET_H
