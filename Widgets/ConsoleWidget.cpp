#include "ConsoleWidget.h"

// Constructor
ConsoleWidget::ConsoleWidget(QWidget *parent) : QWidget(parent)
{
}

void ConsoleWidget::onStartReading()
{
    console = this->findChild<QTextBrowser*>("consoleBrowser");

    if(console == nullptr)
    {
        qDebug("ERROR: Console browser does not exist");
    }

    table->setRowCount(NUM_CELLS);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    for(int i = 0; i < NUM_CELLS; i++)
    {
        table->setItem(i, 0, new QTableWidgetItem(QString::number(i)));
        table->setItem(i, 1, new QTableWidgetItem(QString("No data")));
    }

    qDebug("Button clicked, starting thread\n");

    QThread* thread = new QThread;
    consoleThread = new ConsoleThread();
    consoleThread->moveToThread(thread);

    // Connect the required signals for a QThread
    connect(consoleThread, SIGNAL(error(QString)), this, SLOT(errorString(QString)));
    connect(thread, SIGNAL(started()), consoleThread, SLOT(start()));
    connect(consoleThread, SIGNAL(finished()), thread, SLOT(quit()));
    connect(consoleThread, SIGNAL(finished()), consoleThread, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

    connect(consoleThread, SIGNAL(newPacket(BatteryPacket)), this, SLOT(newPacket(BatteryPacket)));

    thread->start();
}

void ConsoleWidget::onStopReading()
{
    // TODO implement this
}

// Called when a new packet is read
void ConsoleWidget::newPacket(ConsolePacket packet)
{
    // Put the charge value in the appropriate table cell
    int row = packet.cellNum;

    table->item(row, 1)->setText(QString::number(packet.charge));
}

void ConsoleWidget::errorString(QString error)
{
    qCritical("%s \n", qPrintable(error));
}
