#ifndef LOGGINGMANAGER_H
#define LOGGINGMANAGER_H

#include <QObject>
#include "Threads/Packets.h"

class LoggingManager : public QObject
{
    Q_OBJECT
public:
    explicit LoggingManager(QObject *parent = nullptr);

    inline static bool isDriving(){return driving;}
    inline static bool isRecordingCAN(){return recordingCAN;}
    inline static bool isRecordingCamera(){return recordingCamera;}
    inline static bool isRecordingLidar(){return recordingLidar;}
    inline static bool isRecordingGPS(){return recordingGPS;}

    static void setIsDriving(bool status);
    static void setRecordingCAN(bool status);
    static void setRecordingCamera(bool status);
    static void setRecordingLidar(bool status);
    static void setRecordingGPS(bool status);

private:
    static bool driving;
    static bool recordingCAN;
    static bool recordingCamera;
    static bool recordingLidar;
    static bool recordingGPS;
};

#endif // LOGGINGMANAGER_H
