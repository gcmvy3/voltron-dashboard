#include "BatteryWidget.h"

// Constructor
BatteryWidget::BatteryWidget(QWidget *parent) : QWidget(parent)
{
}

void BatteryWidget::onStartReading()
{
    table = this->findChild<QTableWidget*>("batteryTable");

    if(table == nullptr)
    {
        qDebug("ERROR: Battery table does not exist");
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
    batteryThread = new BatteryThread();
    batteryThread->moveToThread(thread);

    // Connect the required signals for a QThread
    connect(batteryThread, SIGNAL(error(QString)), this, SLOT(errorString(QString)));
    connect(thread, SIGNAL(started()), batteryThread, SLOT(start()));
    connect(batteryThread, SIGNAL(finished()), thread, SLOT(quit()));
    connect(batteryThread, SIGNAL(finished()), batteryThread, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

    connect(batteryThread, SIGNAL(newPacket(BatteryPacket)), this, SLOT(newPacket(BatteryPacket)));

    thread->start();
}

void BatteryWidget::onStopReading()
{
    // TODO implement this
}

// Called when a new packet is read
void BatteryWidget::newPacket(BatteryPacket packet)
{
    // Put the charge value in the appropriate table cell
    int row = packet.cellNum;

    table->item(row, 1)->setText(QString::number(packet.charge));
}

void BatteryWidget::errorString(QString error)
{
    qCritical("%s \n", qPrintable(error));
}
