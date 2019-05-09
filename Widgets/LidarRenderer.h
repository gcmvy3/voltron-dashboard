#ifndef LIDARRENDERER_H
#define LIDARRENDERER_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QSemaphore>
#include <QMouseEvent>
#include <vector>

#include "CommunicationManager.h"
#include "Threads/Packets.h"

class LidarRenderer : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    LidarRenderer(QWidget* parent);
    void setXRotation(int angle);
    void setCameraHeight(double height);
    static double degreesToRadians(double degrees);

private:
    int xRot;
    double cameraHeight = 1;

    const int MAX_ZOOM = 5;
    const int MAX_CAM_HEIGHT = 5;

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

    void showEvent( QShowEvent* event) override;
    void hideEvent( QHideEvent* event) override;

    QPoint lastTouchedPos;

    int sharedMemoryFD;
    struct LIDARData* memoryRegions;

    QOpenGLBuffer* buffer;
    QOpenGLShaderProgram* program;

    float aspect;
    double zoom;

    uint posLoc;
    uint colLoc;
    int transformLoc;

    int renderBlock = 0;
    std::vector<int> dirtyBlocks;
    QSemaphore semaphore;

public slots:
    void onPacket(LIDARPacket);
    void setZoomPercentage(double);
};

#endif // LIDARRENDERER_H
