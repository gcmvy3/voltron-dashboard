#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    CommunicationManager::init();
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::chooseCANCodeFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, ("Open File"), QDir::currentPath(), ("JSON Files (*.json)"));
    if(!fileName.isNull())
    {
        QFile* file = new QFile(fileName);
        CANCodeManager::loadFromFile(file);
    }
}


