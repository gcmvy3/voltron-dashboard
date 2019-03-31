#include "BatteryWidget.h"

// Constructor
BatteryWidget::BatteryWidget(QWidget *parent) : QTableWidget(parent)
{
    this->setRowCount(NUM_CELLS);
    this->setColumnCount(2);
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);

    for(int i = 0; i < NUM_CELLS; i++)
    {
        this->setItem(i, 0, new QTableWidgetItem(QString::number(i)));
        this->setItem(i, 1, new QTableWidgetItem(QString("No data")));
    }
}

// Called when a new packet is read
void BatteryWidget::newPacket(BatteryPacket packet)
{
    qDebug("Received new packet");

    int row = packet.cellNum;

    this->item(row, 1)->setText(QString::number(packet.charge));
}
