/*!
   \class CameraRenderer
   \inherits QLabel
   \brief The CameraRenderer class is a custom widget which manages interactions with shared memory for the purpose of displaying Stereoscopic depth video data from the Voltron Core process.

   \ingroup voltron
   \ingroup vstereo

   This widget establishes access to shared memory set up by the Voltron Core process and waits for packets from \l StereoThread.
   These packets are used to determine where new video frames have been placed in shared memory.
   Upon receiving a packet, the widget updates what \l QImage it is displaying based on this information.

   \sa StereoThread, StereoWidget
*/


#include "CameraRenderer.h"

#include <fcntl.h>
#include <sys/mman.h>

/*!
 * Constructs a CameraRenderer label. Connects the widget to incoming packets from \l SteroThread.
 * Additionally, attempts to establish access to shared memory reserved for CameraWidget display data.
 * If this connection is successful, then the data in shared memory is cast into an array of CameraData structs.
 * An array of \l QImage objects are then defined using video data from these structs, with each object pointing to one of these structs in shared memory.
 */
CameraRenderer::CameraRenderer(QWidget *parent) : QLabel(parent), semaphore(1)
{
    sharedMemoryFD = shm_open(CAM_MEMORY_NAME, O_RDONLY, 0777);
    if (sharedMemoryFD == -1)
    {
        CommunicationManager::printToConsole("ERROR: STEREO shared memory could not be established");
    }

    size_t dataSize = sizeof(struct CameraData) * CAM_NUM_IMAGES;
    memoryRegions = (CameraData*)mmap(NULL, dataSize, PROT_READ, MAP_SHARED, sharedMemoryFD, 0);
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

    connect(CommunicationManager::cameraThread, SIGNAL(newPacket(CameraPacket)), this, SLOT(onPacket(CameraPacket)));
}

void CameraRenderer::setDisplayType(int type)
{
    displayType = type;
}

/*!
 * Executed when a \l StereoThread object signals a new Stereo packet to be processed.
 *
 * Updates which \l QImage is being displayed by the CameraRenderer label based on the index provided by \a packet.
 */
void CameraRenderer::onPacket(CameraPacket packet)
{
    if(semaphore.tryAcquire(1))
    {
        if(displayType == DisplayType::DEPTH)
        {
            for (int i = 0; i < CAM_WIDTH; i++)
                for (int j = 0; j < CAM_HEIGHT; j++)
                {
                    depthMemory[j + i * CAM_HEIGHT] = static_cast<unsigned char>((1.0 - memoryRegions[packet.updated].depth[i][j] / 20000.0)  * 255);
                }

            this->setPixmap(QPixmap::fromImage(depthFrame).scaled(this->size(), Qt::KeepAspectRatio, Qt::FastTransformation));
        }
        else if(displayType == DisplayType::STEREO)
        {
            this->setPixmap(QPixmap::fromImage(stereoFrames[packet.updated]).scaled(this->size(), Qt::KeepAspectRatio, Qt::FastTransformation));
        }

        semaphore.release(1);
    }
    else
    {
        qDebug() << "Failed to acquire semaphore";
    }
}
