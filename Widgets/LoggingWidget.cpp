/*!
   \class LoggingWidget
   \inherits QWidget
   \brief The LoggingWidget class is a custom widget which allows the user to control how data is recorded by the Voltron Logging process.

   \ingroup voltron
   \ingroup vlogging

   This widget contains multiple \l QPushButton child widgets, which when pressed will result in the \l LoggingThread sending a packet to the Logging process, telling it to start or stop
   recording the corresponding data from the Core process.

   \sa LoggingThread, LoggingManager
*/

#include "LoggingWidget.h"

/*!
 * Constructs a Logging widget.
 */
LoggingWidget::LoggingWidget(QWidget *parent) : QWidget(parent)
{

}

/*!
 * \overload showEvent( QShowEvent* event )
 *
 * Called automatically when the widget is shown.
 * Initializes the child \l QPushButtons widgets if necessary, updates their status.
 */
void LoggingWidget::showEvent( QShowEvent* event )
{
    QWidget::showEvent( event );

    if(!initialized)
    {
        initialize();
    }
    updateButtonStatus();
}

/*!
 * Sets up the child \l QPushButton widgets and connects them to functions used to communicate with the \l LoggingManager.
 */
void LoggingWidget::initialize()
{
    widgetIndex = DashboardUtils::getWidgetIndex(this);

    QString idSuffix = "";
    if(widgetIndex != -1)
    {
        idSuffix = QString("_").append(QString::number(widgetIndex));
    }

    startDriveButton = findChild<QPushButton*>("startDriveButton" + idSuffix);
    endDriveButton = findChild<QPushButton*>("endDriveButton" + idSuffix);
    canRecordButton = findChild<QPushButton*>("canRecordButton" + idSuffix);
    gpsRecordButton = findChild<QPushButton*>("gpsRecordButton" + idSuffix);
    lidarRecordButton = findChild<QPushButton*>("lidarRecordButton" + idSuffix);
    cameraRecordButton = findChild<QPushButton*>("cameraRecordButton" + idSuffix);

    QObject::connect(startDriveButton, &QPushButton::clicked, this, &LoggingWidget::onStartDriveButtonPressed);
    QObject::connect(endDriveButton, &QPushButton::clicked, this, &LoggingWidget::onEndDriveButtonPressed);
    QObject::connect(canRecordButton, &QPushButton::clicked, this, &LoggingWidget::onCANRecordButtonPressed);
    QObject::connect(gpsRecordButton, &QPushButton::clicked, this, &LoggingWidget::onGPSRecordButtonPressed);
    QObject::connect(lidarRecordButton, &QPushButton::clicked, this, &LoggingWidget::onLidarRecordButtonPressed);
    QObject::connect(cameraRecordButton, &QPushButton::clicked, this, &LoggingWidget::onCameraRecordButtonPressed);

    initialized = true;
}

/*!
 * Updates status of buttons in case the logging status was changed off-screen
 */
void LoggingWidget::updateButtonStatus()
{
    startDriveButton->setEnabled(!LoggingManager::isDriving());
    endDriveButton->setEnabled(LoggingManager::isDriving());

    if(LoggingManager::isDriving())
    {
        canRecordButton->setEnabled(true);
        cameraRecordButton->setEnabled(true);
        gpsRecordButton->setEnabled(true);
        lidarRecordButton->setEnabled(true);
    }
    else
    {
        canRecordButton->setEnabled(false);
        cameraRecordButton->setEnabled(false);
        gpsRecordButton->setEnabled(false);
        lidarRecordButton->setEnabled(false);
    }

    if(LoggingManager::isRecordingCAN())
    {
        canRecordButton->setText(" Stop Recording");
    }
    else
    {
        canRecordButton->setText("Start Recording");
    }

    if(LoggingManager::isRecordingGPS())
    {
        gpsRecordButton->setText(" Stop Recording");
    }
    else
    {
        gpsRecordButton->setText("Start Recording");
    }

    if(LoggingManager::isRecordingLidar())
    {
        lidarRecordButton->setText(" Stop Recording");
    }
    else
    {
        lidarRecordButton->setText("Start Recording");
    }

    if(LoggingManager::isRecordingCamera())
    {
        cameraRecordButton->setText(" Stop Recording");
    }
    else
    {
        cameraRecordButton->setText("Start Recording");
    }
}

/*!
 * Executed when the startDriveButton \l QPushButton widget is pressed.
 *
 * Relays input to the \l LoggingManager, which will send a corresponding packet to the Logging process.
 * Updates all affected buttons to appropriate state for button pressed.
 */
void LoggingWidget::onStartDriveButtonPressed()
{
    LoggingManager::setIsDriving(true);
    startDriveButton->setEnabled(false);
    endDriveButton->setEnabled(true);

    canRecordButton->setEnabled(true);
    cameraRecordButton->setEnabled(true);
    gpsRecordButton->setEnabled(true);
    lidarRecordButton->setEnabled(true);
}

/*!
 * Executed when the endDriveButton \l QPushButton widget is pressed.
 *
 * Relays input to the \l LoggingManager, which will send a corresponding packet to the Logging process.
 * Updates all affected buttons to appropriate state for button pressed.
 */
void LoggingWidget::onEndDriveButtonPressed()
{
    LoggingManager::setIsDriving(false);
    startDriveButton->setEnabled(true);
    endDriveButton->setEnabled(false);
    cameraRecordButton->setText("Start Recording");
    canRecordButton->setText("Start Recording");
    lidarRecordButton->setText("Start Recording");
    gpsRecordButton->setText("Start Recording");

    canRecordButton->setEnabled(false);
    cameraRecordButton->setEnabled(false);
    gpsRecordButton->setEnabled(false);
    lidarRecordButton->setEnabled(false);
}

/*!
 * Executed when the canRecordButton \l QPushButton widget is pressed.
 *
 * Relays input to the \l LoggingManager, which will send a corresponding packet to the Logging process.
 * Updates all affected buttons to appropriate state for button pressed.
 */
void LoggingWidget::onCANRecordButtonPressed()
{
    if(LoggingManager::isRecordingCAN())
    {
        LoggingManager::setRecordingCAN(false);
        canRecordButton->setText("Start Recording");
    }
    else
    {
        LoggingManager::setRecordingCAN(true);
        canRecordButton->setText(" Stop Recording");
    }
}

/*!
 * Executed when the gpsRecordButton \l QPushButton widget is pressed.
 *
 * Relays input to the \l LoggingManager, which will send a corresponding packet to the Logging process.
 * Updates all affected buttons to appropriate state for button pressed.
 */
void LoggingWidget::onGPSRecordButtonPressed()
{
    if(LoggingManager::isRecordingGPS())
    {
        LoggingManager::setRecordingGPS(false);
        gpsRecordButton->setText("Start Recording");
    }
    else
    {
        LoggingManager::setRecordingGPS(true);
        gpsRecordButton->setText(" Stop Recording");
    }
}

/*!
 * Executed when the lidarRecordButton \l QPushButton widget is pressed.
 *
 * Relays input to the \l LoggingManager, which will send a corresponding packet to the Logging process.
 * Updates all affected buttons to appropriate state for button pressed.
 */
void LoggingWidget::onLidarRecordButtonPressed()
{
    if(LoggingManager::isRecordingLidar())
    {
        LoggingManager::setRecordingLidar(false);
        lidarRecordButton->setText("Start Recording");
    }
    else
    {
        LoggingManager::setRecordingLidar(true);
        lidarRecordButton->setText(" Stop Recording");
    }
}

/*!
 * Executed when the cameraRecordButton \l QPushButton widget is pressed.
 *
 * Relays input to the \l LoggingManager, which will send a corresponding packet to the Logging process.
 * Updates all affected buttons to appropriate state for button pressed.
 */
void LoggingWidget::onCameraRecordButtonPressed()
{
    if(LoggingManager::isRecordingCamera())
    {
        LoggingManager::setRecordingCamera(false);
        cameraRecordButton->setText("Start Recording");
    }
    else
    {
        LoggingManager::setRecordingCamera(true);
        cameraRecordButton->setText(" Stop Recording");
    }
}
