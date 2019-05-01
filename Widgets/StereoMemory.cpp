#include "StereoMemory.h"

#include <fcntl.h>
#include <sys/mman.h>

StereoMemory::StereoMemory(QWidget *parent) : QLabel(parent), semaphore(1)
{
    connect(CommunicationManager::stereoThread, SIGNAL(newPacket(StereoPacket)), this, SLOT(onPacket(StereoPacket)));

    sharedMemoryFD = shm_open(CAM_MEMORY_NAME, O_RDONLY, 0777);
    if (sharedMemoryFD == -1)
    {
        CommunicationManager::printToConsole("ERROR: STEREO shared memory could not be established");
    }

    size_t dataSize = sizeof(struct StereoData) * CAM_NUM_IMAGES;
    memoryRegions = (StereoData*)mmap(NULL, dataSize, PROT_READ, MAP_SHARED, sharedMemoryFD, 0);
    if (memoryRegions == MAP_FAILED)
    {
        CommunicationManager::printToConsole("ERROR: STEREO shared memory was established, but could not be mapped");
    }

    for (int i = 0; i < CAM_NUM_IMAGES; i++)
    {
        memReg = (unsigned char*)&memoryRegions[i].rgbImage;
        frame[i] = QImage(memReg, CAM_WIDTH*2, CAM_HEIGHT, QImage::Format_ARGB32);
    }

}

void StereoMemory::onPacket(StereoPacket packet)
{

    semaphore.acquire(1);
    this->setAlignment(Qt::AlignCenter);
    this->setPixmap(QPixmap::fromImage(frame[packet.updated]).scaled(this->size(), Qt::KeepAspectRatio, Qt::FastTransformation));

    semaphore.release(1);
}
