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
}

MainWindow::~MainWindow()
{
    delete ui;
}


