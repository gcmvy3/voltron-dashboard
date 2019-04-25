#include "ConsoleWidget.h"

// Constructor
ConsoleWidget::ConsoleWidget(QWidget *parent) : QWidget(parent)
{
}

/**
 * Called automatically when the widget is shown.
 * Connects the widget to the incoming data packets.
 **/
void ConsoleWidget::showEvent( QShowEvent* event )
{
    QWidget::showEvent( event );
    onStartReading();
}

/**
 * Called automatically when the widget is shown.
 * Disconnects the widget from the incoming data packets for better performance.
 **/
void ConsoleWidget::hideEvent( QHideEvent* event )
{
    QWidget::hideEvent( event );
    onStopReading();
}


void ConsoleWidget::onStartReading()
{
    console = this->findChild<QTextBrowser*>("consoleBrowser");

    if(console == nullptr)
    {
        qDebug("ERROR: Console browser does not exist");
    }

    connect(CommunicationManager::consoleThread, SIGNAL(newPacket(ConsolePacket)), this, SLOT(newPacket(ConsolePacket)));
}

void ConsoleWidget::onStopReading()
{
    disconnect(CommunicationManager::consoleThread, SIGNAL(newPacket(ConsolePacket)), this, SLOT(newPacket(ConsolePacket)));
}

// Called when a new packet is read
void ConsoleWidget::newPacket(ConsolePacket packet)
{
    // Append the message with its timestamp to the console TextBrowser
    QString timeStamp = QDateTime::currentDateTime().toString("hh:mm:ss.zzz");
    QString message = QString("[" + timeStamp + "] " + QString::fromStdString(packet.message));
    console->append(message);
}

void ConsoleWidget::errorString(QString error)
{
    qCritical("%s \n", qPrintable(error));
}
