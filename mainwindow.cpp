#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QThread>

#include "Threads/BatteryThread.h"
#include "Threads/Packets.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_batteryReadButton_toggled(bool checked)
{
    if(checked)
    {
        qDebug("Button clicked, starting thread\n");

        QThread* thread = new QThread;
        batteryThread = new BatteryThread();
        batteryThread->moveToThread(thread);

        connect(batteryThread, SIGNAL(error(QString)), this, SLOT(errorString(QString)));
        connect(thread, SIGNAL(started()), batteryThread, SLOT(start()));
        connect(batteryThread, SIGNAL(finished()), thread, SLOT(quit()));
        connect(batteryThread, SIGNAL(finished()), batteryThread, SLOT(deleteLater()));
        connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
        connect(batteryThread, SIGNAL(newPacket(BatteryPacket)), this, SLOT(on_newBatteryPacket(BatteryPacket)));
        thread->start();
    }
    else
    {
        //TODO close battery thread here
    }
}

void MainWindow::on_newBatteryPacket(BatteryPacket packet)
{
    qDebug("New battery packet!\n");
    qDebug("Cell: %d\n", packet.cellNum);
    qDebug("Charge: %f\n", packet.charge);
}

void MainWindow::errorString(QString error)
{
    qCritical("%s \n", qPrintable(error));
}
