#include "BatteryWidget.h"

// Constructor
BatteryWidget::BatteryWidget(QWidget *parent) : QWidget(parent)
{
    setWindowTitle(QString("Battery Data"));

    toggleButton = new QPushButton(this);
    toggleButton->setText("Read Data");
    toggleButton->setCheckable(true);
    connect(toggleButton, SIGNAL(toggled(bool)), this, SLOT(onStartReading()));

    table = new QTableWidget(this);
    table->setRowCount(NUM_CELLS);
    table->setColumnCount(2);

    QStringList tableHeaders;
    tableHeaders << "Cell Number" << "Charge Level";
    table->setHorizontalHeaderLabels(tableHeaders);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    table->verticalHeader()->hide();
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    for(int i = 0; i < NUM_CELLS; i++)
    {
        table->setItem(i, 0, new QTableWidgetItem(QString::number(i)));
        table->setItem(i, 1, new QTableWidgetItem(QString("No data")));
    }

    this->setMinimumSize(400, 400);

}

// Called when a new packet is read
void BatteryWidget::newPacket(BatteryPacket packet)
{
    qDebug("Received new packet");

    int row = packet.cellNum;

    table->item(row, 1)->setText(QString::number(packet.charge));
}

void BatteryWidget::onButtonToggled(bool buttonChecked)
{
    if(buttonChecked)
    {
        onStartReading();
    }
    else
    {
        onStopReading();
    }
}

void BatteryWidget::onStartReading()
{
    qDebug("Button clicked, starting battery thread\n");

    QThread* thread = new QThread();
    batteryThread = new BatteryThread();
    batteryThread->moveToThread(thread);

    // Connect the required signals for a QThread
    connect(batteryThread, SIGNAL(error(QString)), this, SLOT(errorString(QString)));
    connect(thread, SIGNAL(started()), batteryThread, SLOT(start()));
    connect(batteryThread, SIGNAL(finished()), thread, SLOT(quit()));
    connect(batteryThread, SIGNAL(finished()), batteryThread, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

    // Connect the battery thread to the battery widget
    connect(batteryThread, SIGNAL(newPacket(BatteryPacket)), this, SLOT(newPacket(BatteryPacket)));

    thread->start();
}

void BatteryWidget::onStopReading()
{
    //TODO implement this
}
