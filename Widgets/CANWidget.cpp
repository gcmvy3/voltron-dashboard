/*!
   \class CANWidget
   \inherits QWidget
   \brief The CANWidget class is a custom widget which displays the value of certain CAN codes in real time.
   \ingroup voltron
   \ingroup vCAN

   This widget shows a list of all CAN codes currently loaded by CANCodeManager. It is updated via signals when new CAN codes are loaded.
   When CANThread receives an updated CAN value, it emits a signal that updates every CANWidget automatically.

   \sa CANThread, CANCode, CANCodeManager
*/

#include "CANWidget.h"

/*!
 * Constructs a CAN widget and connects the widget to...
 */
CANWidget::CANWidget(QWidget *parent) : QWidget(parent)
{
    codesTable = nullptr;

    // Connect signals so the table gets automatically populated when new codes are loaded
    QObject::connect(CANCodeManager::getInstance(), &CANCodeManager::newCodesLoaded, this, &CANWidget::updateTable);
    QObject::connect(CommunicationManager::canThread, &CANThread::newPacket, this, &CANWidget::onPacket);
}

bool CANWidget::event(QEvent *event)
{
   bool returnValue = QWidget::event(event);
   if (event->type() == QEvent::Polish)
   {
       initialize();
   }
   return returnValue;
}

void CANWidget::initialize()
{
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

    if(!CANCodeManager::getInstance()->codes.isEmpty())
    {
        qDebug() << "Found existing codes";
        updateTable(CANCodeManager::getInstance()->codes);
    }
    else
    {
        qDebug() << "CAN Codes is empty";
    }
}

/**
 * @brief CANWidget::updateTable Clears the table then populates it with one row for every CAN code.
 * @param newCodes A vector of CANCode objects representing the new set of CAN codes.
 */
void CANWidget::updateTable(QVector<CANCode*> newCodes)
{
    clearTable();

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

void CANWidget::clearTable()
{
    if(codesTable != nullptr)
    {
        codesTable->clearContents();
        codesTable->setRowCount(0);
    }
}

/**
 * @brief CANWidget::updateValue Updates a single value in the table based on a CANDataPacket. Discards the packet if the sender ID does not match the existing entry
 * (happens if new codes have been loaded).
 * @param packet A packet containing the new data.
 */
void CANWidget::onPacket(CANDataPacket packet)
{
    if(codesTable != nullptr && codesTable->rowCount() > packet.pktId)
    {
        // Check existing sender ID
        QTableWidgetItem* entry = codesTable->item(packet.pktId, 5);
        if(entry != nullptr)
        {
            QTableWidgetItem* senderIDItem = codesTable->item(packet.pktId, 2);
            if(senderIDItem != nullptr && !senderIDItem->text().isNull())
            {
                bool success;
                int existingSenderID = senderIDItem->text().toInt(&success, 16);
                // If sender IDs match, update the table with the new value
                if(success && existingSenderID == packet.sender)
                {
                    int startBit = codesTable->item(packet.pktId, 3)->text().toInt();
                    int endBit = codesTable->item(packet.pktId, 4)->text().toInt();
                    if(startBit >=0 && endBit <= 63)
                    {
                        // Extract the designated bits from the chars
                        QVector<bool> bits = QVector<bool>();
                        for(int i = startBit; i <= endBit; i++)
                        {
                            int byteIndex = i / 8;
                            char c = packet.data[byteIndex];
                            bool bitValue = c & (0b10000000 >> i % 8);
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
}
