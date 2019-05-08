/*!
   \class BatteryWidget
   \inherits QWidget
   \brief The BatteryWidget class is a custom widget which displays data sent to it in Battery packets.

   \ingroup voltron
   \ingroup vbattery

   This widget contains a \l QTableWidget child widget, which displays the battery charge data sent to the BatteryWidget via signals.
   The data is displayed in a table with each row corresponding to a charge value.
   Battery packets sent to this widget specify which row of the table will be updated with the provided charge value.

   \note While this and the \l BatteryThread classes are fully implemented, the Voltron Core process, at present, does not send true battery data.

   \sa BatteryThread
*/

#include "BatteryWidget.h"

// Constructor
/*!
 * Constructs a Battery widget.
 */
BatteryWidget::BatteryWidget(QWidget *parent) : QWidget(parent)
{
}

/*!
 * \overload showEvent( QShowEvent* event )
 *
 * This function is automatically called when the widget is shown.
 * Connects the widget to the incoming data packets.
 *
 * \sa QWidget::showEvent( QShowEvent* event )
 */
void BatteryWidget::showEvent( QShowEvent* event )
{
    QWidget::showEvent( event );
    onStartReading();
}

/*!
 * \overload hideEvent( QHideEvent* event )
 *
 * This function is called automatically when the widget is shown.
 * Disconnects the widget from the incoming data packets for better performance.
 *
 * \sa QWidget::hideEvent( QHideEvent* event )
 */
void BatteryWidget::hideEvent( QHideEvent* event )
{
    QWidget::hideEvent( event );
    onStopReading();
}

/*!
 * Connect the widget to the incoming data packets and sets up the table which will be displaying packet data.
 */
void BatteryWidget::onStartReading()
{
    widgetIndex = DashboardUtils::getWidgetIndex(this);

    QString idSuffix = "";
    if(widgetIndex != -1)
    {
        idSuffix = QString("_").append(QString::number(widgetIndex));
    }

    table = this->findChild<QTableWidget*>("batteryTable" + idSuffix);

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

    connect(CommunicationManager::batteryThread, SIGNAL(newPacket(BatteryPacket)), this, SLOT(onPacket(BatteryPacket)));
}

/*!
 * Disconnects the widget from the incoming data packets for better performance.
 */
void BatteryWidget::onStopReading()
{
    disconnect(CommunicationManager::batteryThread, SIGNAL(newPacket(BatteryPacket)), this, SLOT(onPacket(BatteryPacket)));
}

// Called when a new packet is read
/*!
 * Executed when a \l BatteryThread object signals a new Battery packet to be processed.
 *
 * Updates the cell of the child \l QTableWidget table indicated by the \a packet struct with the charge value also provided by the \a packet struct.
 */
void BatteryWidget::onPacket(BatteryPacket packet)
{
    // Put the charge value in the appropriate table cell
    int row = packet.cellNum;

    table->item(row, 1)->setText(QString::number(packet.charge).append(" (Mock data)"));
}

/*!
 * Calls the message handler with the critical error \a error.
 *
 * \sa qCritical()
 */
void BatteryWidget::errorString(QString error)
{
    qCritical("%s \n", qPrintable(error));
}
