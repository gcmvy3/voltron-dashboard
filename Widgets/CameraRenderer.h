#ifndef CAMERARENDERER_H
#define CAMERARENDERER_H

#include <QLabel>
#include <QImage>
#include <QSemaphore>

#include "CommunicationManager.h"
#include "Threads/Packets.h"

class CameraRenderer : public QLabel
{
    Q_OBJECT
public:    
    CameraRenderer(QWidget *parent);
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
    struct CameraData* memoryRegions;

    QSemaphore semaphore;

signals:
    void newFrame(QImage image);

public slots:
    void onPacket(CameraPacket);
};

#endif // CAMERARENDERER_H
