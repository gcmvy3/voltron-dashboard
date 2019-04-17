#ifndef LIDARRENDERER_H
#define LIDARRENDERER_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QSemaphore>
#include <vector>
#include "CommunicationManager.h"

class LidarRenderer : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    LidarRenderer(QWidget* parent);

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    int sharedMemoryFD;
    struct LIDARData* memoryRegions;

    QOpenGLBuffer* buffer;
    QOpenGLShaderProgram* program;

    float aspect;

    uint posLoc;
    uint colLoc;
    int transformLoc;

    std::vector<int> dirtyBlocks;
    QSemaphore semaphore;

public slots:
    void onPacket(LidarPacket);
};

#endif // LIDARRENDERER_H
