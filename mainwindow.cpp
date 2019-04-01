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

void MainWindow::errorString(QString error)
{
    qCritical("%s \n", qPrintable(error));
}
