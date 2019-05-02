#include "StereoWidget.h"

StereoWidget::StereoWidget(QWidget *parent) : QWidget(parent)
{
    StereoWidget::title = new QLabel(this);
    title->setText("Camera View");
    title->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    StereoWidget::display = new StereoMemory(this);
    display->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(title);
    layout->addWidget(display);
    setLayout(layout);
}

// Called when a new packet is read
void StereoWidget::newFrame(QImage frame)
{
    qDebug() << "StereoWidget::newFrame got called";
    display->setAlignment(Qt::AlignCenter);
    display->setPixmap(QPixmap::fromImage(frame).scaled(display->size(), Qt::KeepAspectRatio, Qt::FastTransformation));
}
