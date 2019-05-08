/*!
   \class StereoMemory
   \inherits QLabel
   \brief The StereoMemory class is a custom widget which manages interactions with shared memory for the purpose of displaying Stereoscopic depth video data from the Voltron Core process.

   \ingroup voltron
   \ingroup vstereo

   This widget establishes access to shared memory set up by the Voltron Core process and waits for packets from \l StereoThread.
   These packets are used to determine where new video frames have been placed in shared memory.
   Upon receiving a packet, the widget updates what \l QImage it is displaying based on this information.

   \sa StereoThread, StereoWidget
*/


#include "StereoMemory.h"

#include <fcntl.h>
#include <sys/mman.h>

/*!
 * Constructs a StereoMemory label. Connects the widget to incoming packets from \l SteroThread.
 * Additionally, attempts to establish access to shared memory reserved for StereoWidget display data.
 * If this connection is successful, then the data in shared memory is cast into an array of StereoData structs.
 * An array of \l QImage objects are then defined using video data from these structs, with each object pointing to one of these structs in shared memory.
 */
StereoMemory::StereoMemory(QWidget *parent) : QLabel(parent), semaphore(1)
{
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

    depthMemory = (unsigned char*)malloc(CAM_WIDTH * CAM_HEIGHT);
    depthFrame = QImage((const unsigned char*)depthMemory, CAM_WIDTH, CAM_HEIGHT, QImage::Format_Grayscale8);

    for (int i = 0; i < CAM_NUM_IMAGES; i++)
    {
        stereoFrames[i] = QImage((unsigned char*)&memoryRegions[i].rgbImage, CAM_WIDTH*2, CAM_HEIGHT, QImage::Format_ARGB32);
    }

    connect(CommunicationManager::stereoThread, SIGNAL(newPacket(StereoPacket)), this, SLOT(onPacket(StereoPacket)));
}

void StereoMemory::setDisplayType(int type)
{
    displayType = type;
}

/*!
 * Executed when a \l StereoThread object signals a new Stereo packet to be processed.
 *
 * Updates which \l QImage is being displayed by the StereoMemory label based on the index provided by \a packet.
 */
void StereoMemory::onPacket(StereoPacket packet)
{
    semaphore.acquire(1);
    this->setAlignment(Qt::AlignCenter);
    if(displayType == DisplayType::DEPTH)
    {
        for (int i = 0; i < CAM_WIDTH; i++)
            for (int j = 0; j < CAM_HEIGHT; j++)
            {
                depthMemory[i + j * CAM_WIDTH] = (unsigned char)(memoryRegions[packet.updated].depth[i][j] * 255);
            }

        this->setPixmap(QPixmap::fromImage(depthFrame).scaled(this->size(), Qt::KeepAspectRatio, Qt::FastTransformation));
    }
    else if(displayType == DisplayType::STEREO)
    {
        this->setPixmap(QPixmap::fromImage(stereoFrames[packet.updated]).scaled(this->size(), Qt::KeepAspectRatio, Qt::FastTransformation));
    }

    semaphore.release(1);
}
