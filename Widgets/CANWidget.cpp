#include "CANWidget.h"

CANWidget::CANWidget(QWidget *parent) : QWidget(parent)
{

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
    }

}
