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
    dirtyBlocks.push_back(packet.updated);
    semaphore.release(1);
}

void StereoMemory::createFrame()
{
    while(true)
    {
        if(semaphore.tryAcquire(1))
        {
            if(dirtyBlocks.size() > 0)
            {
                int newBlock = dirtyBlocks[0];
                dirtyBlocks.erase(dirtyBlocks.begin());
                semaphore.release(1);

                renderBlock = newBlock;
                buffer = &memoryRegions[newBlock];

                frame[newBlock] = new QImage(buffer.getPtr<sl::uchar1>(MEM_CPU), buffer.getHeight(), buffer.getWidth(), QImage::Format_Grayscale8);

                emit(onFrame(frame[newBlock]));

            }
            else
                semaphore.release(1);
        }
    }
}
