/*!
   \class ConsoleWidget
   \inherits QWidget
   \brief The ConsoleWidget class is a custom widget which displays messages sent to it in Console packets.

   \ingroup voltron
   \ingroup vconsole

   This widget contains a \l QTextBrowser child widget, which displays the messages sent to the ConsoleWidget via signals.
   Console packets sent to this widget can also mark its contents as an error message, which will be displayed in red.
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

/*!
 * \overload showEvent( QShowEvent* event )
 *
 * This function is automatically called when the widget is shown.
 * Connects the widget to the incoming data packets.
 *
 * \sa QWidget::showEvent( QShowEvent* event )
 */
void ConsoleWidget::showEvent( QShowEvent* event )
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
void ConsoleWidget::hideEvent( QHideEvent* event )
{
    QWidget::hideEvent( event );
    onStopReading();
}

/*!
 * Connect the widget to the incoming data packets.
 */
void ConsoleWidget::onStartReading()
{
    console = this->findChild<QTextBrowser*>("consoleBrowser");

    if(console == nullptr)
    {
        qDebug("ERROR: Console browser does not exist");
    }

    connect(CommunicationManager::consoleThread, SIGNAL(newPacket(ConsolePacket)), this, SLOT(newPacket(ConsolePacket)));
}

/*!
 * Disconnects the widget from the incoming data packets for better performance.
 */
void ConsoleWidget::onStopReading()
{
    disconnect(CommunicationManager::consoleThread, SIGNAL(newPacket(ConsolePacket)), this, SLOT(newPacket(ConsolePacket)));
}

// Called when a new packet is read
/*!
 * Executed when a \l ConsoleThread object signals a new Console packet to be processed.
 *
 * Generates a \l QString composed of a time stamp followed by the message stored in the \a packet struct.
 * This QString is then displayed in the child \l QTextBrowser widget of the Console widget.
 * If the \a packet struct also flags its message as an error, it will be displayed in red.
 */
void ConsoleWidget::newPacket(ConsolePacket packet)
{
    // Append the message with its timestamp to the console TextBrowser
    QString timeStamp = QDateTime::currentDateTime().toString("hh:mm:ss.zzz");
    QString message = QString("[" + timeStamp + "] " + QString::fromStdString(packet.message));

    //console->setTextColor(Qt::red); Needed for error message text

    console->append(message);
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
