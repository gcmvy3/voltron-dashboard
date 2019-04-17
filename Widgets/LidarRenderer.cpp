#include "LidarRenderer.h"

#include "Threads/Packets.h"

#include <iostream>
#include <algorithm>
#include <sys/mman.h>
#include <fcntl.h>

#include <QMatrix4x4>

LidarRenderer::LidarRenderer(QWidget* parent) : QOpenGLWidget (parent), semaphore(1)
{
    connect(CommunicationManager::lidarThread, SIGNAL(newPacket(LidarPacket)), this, SLOT(onPacket(LidarPacket)));

    sharedMemoryFD = shm_open(LIDAR_MEMORY_NAME, O_RDONLY, 0777);
    if (sharedMemoryFD == -1)
    {
        //BAD STUFF
    }

    size_t dataSize = sizeof(struct LIDARData) * LIDAR_DATA_NUM_REGIONS;
    memoryRegions = (LIDARData*)mmap(NULL, dataSize, PROT_READ, MAP_SHARED, sharedMemoryFD, 0);
    if (memoryRegions == MAP_FAILED)
    {
        //BAD STUFF
    }
}

static const char *vertexShaderSource =
        "attribute vec4 posAttr;\n"
        "varying vec4 col;\n"
        "uniform mat4 matrix;\n"
        "void main() {\n"
        "   col = vec4(1.0, 0.0, 1.0, 1.0);\n"
        "   gl_Position = matrix * vec4(posAttr.xyz, 1.0);\n"
        "}\n";

static const char *fragmentShaderSource =
        "varying vec4 col;\n"
        "void main() {\n"
        "   gl_FragColor = col;\n"
        "}\n";

void LidarRenderer::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0,0,0,1);
    glPointSize(4.0f);

    buffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    buffer->setUsagePattern(QOpenGLBuffer::StreamDraw);
    buffer->create();

    buffer->bind();
    buffer->allocate(sizeof(LIDARData) * LIDAR_DATA_NUM_REGIONS);

    program = new QOpenGLShaderProgram();
    program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    program->link();

    posLoc = program->attributeLocation("posAttr");
    transformLoc = program->uniformLocation("matrix");

    aspect = std::max(this->width(), this->height()) / std::min(this->width(), this->height());

    //void* bufferData = buffer->map(QOpenGLBuffer::ReadWrite);
}

void LidarRenderer::resizeGL(int w, int h)
{
    aspect = std::max(w, h) / std::min(w, h);
}

void LidarRenderer::paintGL()
{
    if (semaphore.tryAcquire(1))
    {
        if (dirtyBlocks.size() > 0)
        {
            int newBlock = dirtyBlocks[0];
            dirtyBlocks.erase(dirtyBlocks.begin());
            semaphore.release(1);

            buffer->write(newBlock * sizeof(LIDARData), &memoryRegions[newBlock], sizeof(LIDARData));

            std::cout << "Uploaded block " << newBlock << std::endl;
        }
        else
            semaphore.release(1);
    }



    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    makeCurrent();

    program->bind();

    QMatrix4x4 transform;
    transform.perspective(60.0f, aspect, 0.1f, 1000.0f);
    transform.translate(0, 0, -2);
    program->setUniformValue(transformLoc, transform);

    glEnableVertexAttribArray(0);
    buffer->bind();
    glVertexAttribPointer(posLoc, 4, GL_FLOAT, GL_FALSE, 0, (void*) 0);
    glDrawArrays(GL_POINTS, 0, LIDAR_DATA_NUM_POINTS * LIDAR_DATA_NUM_REGIONS);
    glDisableVertexAttribArray(0);

    update();
}

void LidarRenderer::onPacket(LidarPacket packet)
{
    semaphore.acquire(1);
    dirtyBlocks.push_back(packet.updated);
    semaphore.release(1);
}
