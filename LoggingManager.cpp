#include "LoggingManager.h"
#include "CommunicationManager.h"

bool LoggingManager::driving = false;
bool LoggingManager::recordingCAN = false;
bool LoggingManager::recordingCamera = false;
bool LoggingManager::recordingLidar = false;
bool LoggingManager::recordingGPS = false;

LoggingManager::LoggingManager(QObject *parent) : QObject(parent)
{

}

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
