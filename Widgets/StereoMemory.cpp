#include "StereoMemory.h"

#include <fcntl.h>
#include <sys/mman.h>

StereoMemory::StereoMemory(QObject *parent) : QObject(parent), semaphore(1)
{
    connect(CommunicationManager::stereoThread, SIGNAL(newPacket(StereoPacket)), this, SLOT(onPacket(StereoPacket)));

    sharedMemoryFD = shm_open(STEREO_MEMORY_NAME, O_RDONLY, 0777);
    if (sharedMemoryFD == -1)
    {
        CommunicationManager::printToConsole("ERROR: STEREO shared memory could not be established");
    }

    size_t dataSize = sizeof(struct StereoData) * STEREO_DATA_NUM_REGIONS;
    memoryRegions = (StereoData*)mmap(NULL, dataSize, PROT_READ, MAP_SHARED, sharedMemoryFD, 0);
    if (memoryRegions == MAP_FAILED)
    {
        CommunicationManager::printToConsole("ERROR: STEREO shared memory was established, but could not be mapped");
    }
}

void StereoMemory::onPacket(StereoPacket packet)
{

    semaphore.acquire(1);

    //frame = new QImage(memoryRegions[packet.updated].data, buffer.getHeight(), buffer.getWidth(), QImage::Format_ARGB32);
    emit(newFrame(frame));

    semaphore.release(1);
}
