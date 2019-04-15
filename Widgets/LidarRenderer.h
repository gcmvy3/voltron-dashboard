#ifndef LIDARRENDERER_H
#define LIDARRENDERER_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class LidarRenderer : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
    LidarRenderer(QWidget* parent);

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

};

#endif // LIDARRENDERER_H
