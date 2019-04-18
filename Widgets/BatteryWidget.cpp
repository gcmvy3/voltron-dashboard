#include "BatteryWidget.h"

// Constructor
BatteryWidget::BatteryWidget(QWidget *parent) : QWidget(parent)
{
}

// Called automatically when the widget is shown
void BatteryWidget::showEvent( QShowEvent* event )
{
    QWidget::showEvent( event );
    onStartReading();
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

    connect(CommunicationManager::batteryThread, SIGNAL(newPacket(BatteryPacket)), this, SLOT(newPacket(BatteryPacket)));
}

void BatteryWidget::onStopReading()
{
    disconnect(CommunicationManager::batteryThread, SIGNAL(newPacket(BatteryPacket)), this, SLOT(newPacket(BatteryPacket)));
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