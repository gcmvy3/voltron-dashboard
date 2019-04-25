#ifndef STEREOMEMORY_H
#define STEREOMEMORY_H

#include <QObject>
#include <QImage>
#include <QSemaphore>

#include "CommunicationManager.h"
#include "Threads/Packets.h"

class StereoMemory : public QObject
{
    Q_OBJECT
public:
    StereoMemory(QObject *parent);

protected:
    QImage frame[STEREO_DATA_NUM_REGIONS];

    int sharedMemoryFD;
    struct StereoData* memoryRegions;

    int renderBlock = 0;
    std::vector<int> dirtyBlocks;
    QSemaphore semaphore;

signals:

public slots:
    void onPacket(StereoPacket);
};

#endif // STEREOMEMORY_H
