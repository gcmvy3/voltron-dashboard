/*!
   \class CANWidget
   \inherits QWidget
   \brief The CANWidget class is a custom widget which ...

   \ingroup voltron
   \ingroup vCAN

   This widget contains ...

   \sa CANThread, CANCode, CANCodeManager
*/

#include "CANWidget.h"

/*!
 * Constructs a CAN widget and connects the widget to...
 */
CANWidget::CANWidget(QWidget *parent) : QWidget(parent)
{
    QObject::connect(CommunicationManager::canThread, &CANThread::newPacket, this, &CANWidget::updateValue);
}

/**
 * Called automatically when the widget is shown.
 * Connects the widget to the incoming data packets.
 **/
void CANWidget::showEvent( QShowEvent* event )
{
    QWidget::showEvent( event );

    widgetIndex = DashboardUtils::getWidgetIndex(this);

    QString idSuffix = "";
    if(widgetIndex != -1)
    {
        idSuffix = QString("_").append(QString::number(widgetIndex));
    }

    // Get pointer to button
    QPushButton* loadCANFileButton = this->findChild<QPushButton*>("loadCANFileButton" + idSuffix);

    if(loadCANFileButton == nullptr)
    {
        qDebug("ERROR: loadCANFileButton does not exist");
    }

    // Connect the button to the file loader code
    QObject::connect(loadCANFileButton, &QPushButton::clicked, CANCodeManager::getInstance(), &CANCodeManager::openCANFile);

    // Get pointer to table
    codesTable = this->findChild<QTableWidget*>("CANCodesTable" + idSuffix);

    if(codesTable == nullptr)
    {
        qDebug("ERROR: CANCodesTable does not exist");
    }

    // Connect signals so the table gets automatically populated when new codes are loaded
    QObject::connect(CANCodeManager::getInstance(), &CANCodeManager::newCodesLoaded, this, &CANWidget::updateTable);
}

/**
 * @brief CANWidget::updateTable Clears the table then populates it with one row for every CAN code.
 * @param newCodes A vector of CANCode objects representing the new set of CAN codes.
 */
void CANWidget::updateTable(QVector<CANCode*> newCodes)
{
    codesTable->clearContents();

    //Add a row to the table for every new can code
    for(int i = 0; i < newCodes.size(); i++)
    {
        int rowIndex = codesTable->rowCount();

        CANCode* code = newCodes.at(i);
        codesTable->insertRow(rowIndex);

        codesTable->setItem(rowIndex, 0, new QTableWidgetItem(QString::number(code->id)));
        codesTable->setItem(rowIndex, 1, new QTableWidgetItem(code->name));
        codesTable->setItem(rowIndex, 2, new QTableWidgetItem(code->senderIDString));
        codesTable->setItem(rowIndex, 3, new QTableWidgetItem(QString::number(code->bitStart)));
        codesTable->setItem(rowIndex, 4, new QTableWidgetItem(QString::number(code->bitEnd)));
        codesTable->setItem(rowIndex, 5, new QTableWidgetItem(QString("No data")));
    }
}

/**
 * @brief CANWidget::updateValue Updates a single value in the table based on a CANDataPacket. Discards the packet if the sender ID does not match the existing entry
 * (happens if new codes have been loaded).
 * @param packet A packet containing the new data.
 */
void CANWidget::updateValue(CANDataPacket packet)
{
    QTableWidgetItem* entry = codesTable->item(packet.id, 5);
    if(entry != nullptr)
    {
        // Check existing sender ID
        QTableWidgetItem* senderIDItem = codesTable->item(packet.id, 2);
        if(senderIDItem != nullptr && !senderIDItem->text().isNull())
        {
            bool success;
            int existingSenderID = senderIDItem->text().toInt(&success, 16);
            // If sender IDs match, update the table with the new value
            if(success && existingSenderID == packet.sender)
            {
                int startBit = codesTable->item(packet.id, 3)->text().toInt();
                int endBit = codesTable->item(packet.id, 4)->text().toInt();
                if(startBit >=0 && endBit <= 63)
                {
                    // Extract the designated bits from the chars
                    QVector<bool> bits = QVector<bool>();
                    for(int i = startBit; i <= endBit; i++)
                    {
                        int byteIndex = i / 8;
                        char c = packet.data[byteIndex];
                        bool bitValue = c & (1 << i % 8);
                        bits.append(bitValue);
                    }
                    // Convert the bit string to a QString for display
                    QString valueString = QString();
                    for(int i = 0; i < bits.size(); i++)
                    {
                        if(bits[i])
                        {
                            valueString.append(QString("1"));
                        }
                        else
                        {
                            valueString.append(QString("0"));
                        }
                    }

                    // Display the value in the table
                    entry->setText(valueString);
                }
            }
        }
    }
}
