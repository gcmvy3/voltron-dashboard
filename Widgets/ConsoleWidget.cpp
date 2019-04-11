#include "ConsoleWidget.h"

// Constructor
ConsoleWidget::ConsoleWidget(QWidget *parent) : QWidget(parent)
{
}

// Called automatically when the widget is shown
void ConsoleWidget::showEvent( QShowEvent* event )
{
    QWidget::showEvent( event );
    onStartReading();
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
    //QString message = "[" + timeStamp + "] " + packet.msg;
    QString message = "Hello world";
    console->append(message);
}

void ConsoleWidget::errorString(QString error)
{
    qCritical("%s \n", qPrintable(error));
}
