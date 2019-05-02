/*!
   \class LidarRenderer
   \inherits QOpenGLWidget
   \brief The LidarRenderer class is a custom widget which manages interactions with shared memory for the purpose of displaying 3-d point-cloud visual data from the Voltron Core process.

   \ingroup voltron
   \ingroup vlidar

   This widget establishes access to shared memory set up by the Voltron Core process and waits for packets from \l LidarThread.
   These packets are used to determine ...

   \sa LidarThread, LidarWidget
*/

#include "LidarRenderer.h"

#include <iostream>
#include <algorithm>
#include <sys/mman.h>
#include <fcntl.h>

#include <QMatrix4x4>

LidarRenderer::LidarRenderer(QWidget* parent) : QOpenGLWidget (parent), semaphore(1)
{
    lastTouchedPos = QPoint(-1,-1);

    connect(CommunicationManager::lidarThread, SIGNAL(newPacket(LidarPacket)), this, SLOT(onPacket(LidarPacket)));

    sharedMemoryFD = shm_open(LIDAR_MEMORY_NAME, O_RDONLY, 0777);
    if (sharedMemoryFD == -1)
    {
        CommunicationManager::printToConsole("ERROR: LIDAR shared memory could not be established");
    }

    size_t dataSize = sizeof(struct LIDARData) * LIDAR_DATA_NUM_REGIONS;
    memoryRegions = (LIDARData*)mmap(NULL, dataSize, PROT_READ, MAP_SHARED, sharedMemoryFD, 0);
    if (memoryRegions == MAP_FAILED)
    {
        CommunicationManager::printToConsole("ERROR: LIDAR shared memory was established, but could not be mapped");
    }
}

static const char *vertexShaderSource =
        "attribute vec4 posAttr;\n"
        "varying vec4 col;\n"
        "uniform mat4 matrix;\n"
        "void main() {\n"
        "   col = vec4(posAttr.w, 0.0, 1.0, 1.0);\n"
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

    xRot = 0;
    yRot = 0;
    zRot = 0;
}

void LidarRenderer::resizeGL(int w, int h)
{
    aspect = std::max(w, h) / std::min(w, h);
    glViewport(0, 0, w, h);
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

            renderBlock = newBlock;
            buffer->write(newBlock * sizeof(LIDARData), &memoryRegions[newBlock], sizeof(LIDARData));
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
    transform.rotate(xRot, 0, 1, 0);
    transform.rotate(yRot, 1, 0, 0);

    program->setUniformValue(transformLoc, transform);

    glEnableVertexAttribArray(0);
    buffer->bind();
    glVertexAttribPointer(posLoc, 4, GL_FLOAT, GL_FALSE, 0, (void*) 0);
    glDrawArrays(GL_POINTS, renderBlock * LIDAR_DATA_NUM_POINTS, LIDAR_DATA_NUM_POINTS);
    glDisableVertexAttribArray(0);

    update();
}

void LidarRenderer::onPacket(LidarPacket packet)
{
    semaphore.acquire(1);
    dirtyBlocks.push_back(packet.updated);
    semaphore.release(1);
}

void LidarRenderer::setXRotation(int angle)
{
    //Normalize angle
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360 * 16)
        angle -= 360 * 16;

    if(angle != xRot)
    {
        xRot = angle;
    }
}

void LidarRenderer::setYRotation(int angle)
{
    //Normalize angle
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360 * 16)
        angle -= 360 * 16;

    if(angle != yRot)
    {
        yRot = angle;
    }
}

void LidarRenderer::mouseMoveEvent(QMouseEvent *event)
{
    if(lastTouchedPos != QPoint(-1, -1))
    {
        int dx = event->x() - lastTouchedPos.x();
        int dy = event->y() - lastTouchedPos.y();

        if(event->buttons() & Qt::LeftButton)
        {
            setXRotation(xRot + dx);
            setYRotation(yRot + dy);
        }
    }

    lastTouchedPos = event->pos();
}

void LidarRenderer::mouseReleaseEvent(QMouseEvent* event)
{
    lastTouchedPos = QPoint(-1,-1);
}

/**
 * Called automatically when the widget is shown.
 * Connects the widget to the incoming data packets.
 **/
void LidarRenderer::showEvent( QShowEvent* event )
{
    QWidget::showEvent( event );
    connect(CommunicationManager::lidarThread, SIGNAL(newPacket(LidarPacket)), this, SLOT(onPacket(LidarPacket)));
}

/**
 * Called automatically when the widget is shown.
 * Disconnects the widget from the incoming data packets for better performance.
 **/
void LidarRenderer::hideEvent( QHideEvent* event )
{
    QWidget::hideEvent( event );
    disconnect(CommunicationManager::lidarThread, SIGNAL(newPacket(LidarPacket)), this, SLOT(onPacket(LidarPacket)));
}
