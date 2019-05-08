/*!
   \class ConsoleWidget
   \inherits QWidget
   \brief The ConsoleWidget class is a custom widget which displays messages sent to it in Console packets.

   \ingroup voltron
   \ingroup vconsole

   This widget contains a \l QTextBrowser child widget, which displays the messages sent to the ConsoleWidget via signals.
   All messages are displayed with a time stamp of when the message was received by the ConsoleWidget.

   \sa ConsoleThread
*/

#include "ConsoleWidget.h"

// Constructor
/*!
 * Constructs a Console widget.
 */
ConsoleWidget::ConsoleWidget(QWidget *parent) : QWidget(parent)
{
}

bool ConsoleWidget::event(QEvent *event)
{
   bool returnValue = QWidget::event(event);
   if (event->type() == QEvent::Polish)
   {
       onStartReading();
   }
   return returnValue;
}

/*!
 * Sets up the child \l QTextBrowser widget.
 * Connect the widget to the incoming data packets.
 */
void ConsoleWidget::onStartReading()
{
    widgetIndex = DashboardUtils::getWidgetIndex(this);

    QString idSuffix = "";
    if(widgetIndex != -1)
    {
        idSuffix = QString("_").append(QString::number(widgetIndex));
    }

    console = this->findChild<QTextBrowser*>("consoleBrowser" + idSuffix);

    if(console == nullptr)
    {
        qDebug("ERROR: Console browser does not exist");
    }

    connect(CommunicationManager::consoleThread, SIGNAL(newPacket(DebugPacket)), this, SLOT(onPacket(DebugPacket)));
}

/*!
 * Disconnects the widget from the incoming data packets for better performance.
 */
void ConsoleWidget::onStopReading()
{
    disconnect(CommunicationManager::consoleThread, SIGNAL(newPacket(DebugPacket)), this, SLOT(onPacket(DebugPacket)));
}

// Called when a new packet is read
/*!
 * Executed when a \l ConsoleThread object signals a new Console packet to be processed.
 *
 * Generates a \l QString composed of a time stamp followed by the message stored in the \a packet struct.
 * This QString is then displayed in the child \l QTextBrowser widget of the Console widget.
 */
void ConsoleWidget::onPacket(DebugPacket packet)
{
    // Append the message with its timestamp to the console TextBrowser
    QString timeStamp = QDateTime::currentDateTime().toString("hh:mm:ss.zzz");
    QString message = QString("[" + timeStamp + "] " + QString(packet.str));

    console->moveCursor (QTextCursor::End);
    console->insertPlainText (message);
    console->moveCursor (QTextCursor::End);
}

/*!
 * Calls the message handler with the critical error \a error.
 *
 * \sa qCritical()
 */
void ConsoleWidget::errorString(QString error)
{
    qCritical("%s \n", qPrintable(error));
}
