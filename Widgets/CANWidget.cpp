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

    QPushButton* loadCANFileButton = this->findChild<QPushButton*>("loadCANFileButton" + idSuffix);

    if(loadCANFileButton == nullptr)
    {
        qDebug("ERROR: loadCANFileButton does not exist");
    }

    QObject::connect(loadCANFileButton, &QPushButton::clicked, &CANCodeManager::openCANFile);
}
