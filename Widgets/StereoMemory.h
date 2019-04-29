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
    QImage frame;

    int sharedMemoryFD;
    struct StereoData* memoryRegions;

    int renderBlock = 0;
    std::vector<int> dirtyBlocks;
    QSemaphore semaphore;

signals:
    void newFrame(QImage image);

public slots:
    void onPacket(StereoPacket);
};

#endif // STEREOMEMORY_H
