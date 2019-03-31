#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Threads/Packets.h"
#include "Threads/BatteryThread.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_batteryReadButton_toggled(bool checked);
    void on_newBatteryPacket(BatteryPacket packet);

    void errorString(QString in);

private:
    Ui::MainWindow *ui;

    BatteryThread *batteryThread;
};

#endif // MAINWINDOW_H
