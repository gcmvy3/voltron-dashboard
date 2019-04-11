#include "ConsoleWidget.h"

// Constructor
ConsoleWidget::ConsoleWidget(QWidget *parent) : QWidget(parent)
{
}

void ConsoleWidget::onStartReading()
{
    console = this->findChild<QTextBrowser*>("consoleBrowser");

    if(console == nullptr)
    {
        qDebug("ERROR: Console browser does not exist");
    }

    qDebug("Button clicked, starting thread\n");

    QThread* thread = new QThread;
    consoleThread = new ConsoleThread();
    consoleThread->moveToThread(thread);

    // Connect the required signals for a QThread
    connect(consoleThread, SIGNAL(error(QString)), this, SLOT(errorString(QString)));
    connect(thread, SIGNAL(started()), consoleThread, SLOT(start()));
    connect(consoleThread, SIGNAL(finished()), thread, SLOT(quit()));
    connect(consoleThread, SIGNAL(finished()), consoleThread, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

    connect(consoleThread, SIGNAL(newPacket(ConsolePacket)), this, SLOT(newPacket(ConsolePacket)));

    thread->start();
}

void ConsoleWidget::onStopReading()
{
    // TODO implement this
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
