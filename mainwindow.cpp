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
    this->findChild<ConsoleWidget*>("consoleWidget")->onStartReading();
    this->findChild<BatteryWidget*>("batteryWidget")->onStartReading();
}

MainWindow::~MainWindow()
{
    delete ui;
}


