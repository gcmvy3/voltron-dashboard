/*!
   \class LoggingManager
   \inherits QObject
   \brief The LoggingManager class is a custom class which determines which deteremines what code to send to the Logging process via \l LoggingThread based on input from \l LoggingWidget.

   \ingroup voltron
   \ingroup vlogging

   This class ensures that the Logging process records only what the user tells it to through input on the dashboard.
   When a button is pressed in the \l LoggingWidget widget, the LoggingManager will create a packet containing a code corresponding to that button press.
   This packet is then sent by the \l LoggingThread object to the Logging process to start or stop logging of the corresponding data set.

   \sa LoggingThread, LoggingWidget
*/

#include "LoggingManager.h"
#include "CommunicationManager.h"

bool LoggingManager::driving = false;
bool LoggingManager::recordingCAN = false;
bool LoggingManager::recordingCamera = false;
bool LoggingManager::recordingLidar = false;
bool LoggingManager::recordingGPS = false;


/*!
 * Constructs a LoggingManager object to manage input from the \l LoggingWidget and the behavior of the Logging process.
 */
LoggingManager::LoggingManager(QObject *parent) : QObject(parent)
{

}

/*!
 * If \a status does not match the current state of \i driving, generates and sends packets to Logging process to indicate the start or stop of a drive and to begin or stop logging all available data.
 */
void LoggingManager::setIsDriving(bool status)
{
    if(driving != status)
    {
        LoggingControlPacket packet = LoggingControlPacket();

        if(driving)
        {
            packet.code = LoggingControlCode::EndDrive;
        }
        else
        {
            packet.code = LoggingControlCode::StartDrive;
            setRecordingCAN(false);
            setRecordingCamera(false);
            setRecordingGPS(false);
            setRecordingLidar(false);
        }

        CommunicationManager::loggingThread->broadcastPacket(packet);
        driving = !driving;
    }
}

/*!
 * If \a status does not match the current state of \i recordingCAN, generates and sends packets to Logging process to tell it to start or stop recording CAN data.
 */
void LoggingManager::setRecordingCAN(bool status)
{
    if(recordingCAN != status)
    {
        LoggingControlPacket packet = LoggingControlPacket();

        if(recordingCAN)
        {
            packet.code = LoggingControlCode::EndCANCapture;
        }
        else
        {
            packet.code = LoggingControlCode::StartCANCapture;
        }

        CommunicationManager::loggingThread->broadcastPacket(packet);
        recordingCAN = !recordingCAN;
    }
}

/*!
 * If \a status does not match the current state of \i recordingCamera, generates and sends packets to Logging process to tell it to start or stop recording Camera data.
 */
void LoggingManager::setRecordingCamera(bool status)
{
    if(recordingCamera != status)
    {
        LoggingControlPacket packet = LoggingControlPacket();

        if(recordingCamera)
        {
            packet.code = LoggingControlCode::EndZEDCapture;
        }
        else
        {
            packet.code = LoggingControlCode::StartZEDCapture;
        }

        CommunicationManager::loggingThread->broadcastPacket(packet);
        recordingCamera = !recordingCamera;
    }
}

/*!
 * If \a status does not match the current state of \i recordingLidar, generates and sends packets to Logging process to tell it to start or stop recording Lidar data.
 */
void LoggingManager::setRecordingLidar(bool status)
{
    if(recordingLidar != status)
    {
        LoggingControlPacket packet = LoggingControlPacket();

        if(recordingLidar)
        {
            packet.code = LoggingControlCode::EndLIDARCapture;
        }
        else
        {
            packet.code = LoggingControlCode::StartLIDARCapture;
        }

        CommunicationManager::loggingThread->broadcastPacket(packet);
        recordingLidar = !recordingLidar;
    }
}

/*!
 * If \a status does not match the current state of \i recordingGPS, generates and sends packets to Logging process to tell it to start or stop recording GPS data.
 */
void LoggingManager::setRecordingGPS(bool status)
{
    if(recordingGPS != status)
    {
        LoggingControlPacket packet = LoggingControlPacket();

        if(recordingGPS)
        {
            packet.code = LoggingControlCode::EndGPSCapture;
        }
        else
        {
            packet.code = LoggingControlCode::StartGPSCapture;
        }

        CommunicationManager::loggingThread->broadcastPacket(packet);
        recordingGPS = !recordingGPS;
    }
}
