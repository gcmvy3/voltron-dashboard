#ifndef STEREOMEMORY_H
#define STEREOMEMORY_H

#include <QLabel>
#include <QImage>
#include <QSemaphore>

#include "CommunicationManager.h"
#include "Threads/Packets.h"

class StereoMemory : public QLabel
{
    Q_OBJECT
public:    
    StereoMemory(QWidget *parent);
    void setDisplayType(int type);

    enum DisplayType
    {
        STEREO = 0,
        DEPTH = 1
    };

    int displayType;

protected:
    QImage stereoFrames[CAM_NUM_IMAGES];

    QImage depthFrame;
    unsigned char* depthMemory;

    int sharedMemoryFD;
    struct StereoData* memoryRegions;

    QSemaphore semaphore;

signals:
    void newFrame(QImage image);

public slots:
    void onPacket(StereoPacket);
};

#endif // STEREOMEMORY_H
