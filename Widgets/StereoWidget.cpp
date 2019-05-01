#include "StereoWidget.h"

StereoMemory* StereoWidget::shmem;

StereoWidget::StereoWidget(QWidget *parent) : QWidget(parent)
{
    shmem = new StereoMemory(this);

    StereoWidget::title = new QLabel(this);
    title->setText("Stereoscopic View");
    title->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    StereoWidget::display = new QLabel(this);
    display->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(title);
    layout->addWidget(display);
    setLayout(layout);
}

/**
 * Called automatically when the widget is shown.
 * Connects the widget to the incoming data packets.
 **/
void StereoWidget::showEvent( QShowEvent* event )
{
    QWidget::showEvent( event );
    onStartReading();
}

/**
 * Called automatically when the widget is shown.
 * Disconnects the widget from the incoming data packets for better performance.
 **/
void StereoWidget::hideEvent( QHideEvent* event )
{
    QWidget::hideEvent( event );
    onStopReading();
}

void StereoWidget::onStartReading()
{
    connect(shmem, SIGNAL(newFrame(QImage)), this, SLOT(newFrame(QImage)));
}

void StereoWidget::onStopReading()
{
    disconnect(shmem, SIGNAL(newFrame(QImage)), this, SLOT(newFrame(QImage)));
}

// Called when a new packet is read
void StereoWidget::newFrame(QImage frame)
{
    display->setAlignment(Qt::AlignCenter);
    display->setPixmap(QPixmap::fromImage(frame).scaled(display->size(), Qt::KeepAspectRatio, Qt::FastTransformation));
}
