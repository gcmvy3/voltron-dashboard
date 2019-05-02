/*!
   \class LidarWidget
   \inherits QWidget
   \brief The LidarWidget class is a custom widget which displays 3-d point cloud visual data obtained from shared memory.

   \ingroup voltron
   \ingroup vlidar

   This widget contains a \l LidarRenderer child widget, which displays view of the 3-d space generated using data from shared memory.
   This widget creates and manages its child widgets automatically upon construction of the widget.

   \sa LidarThread, LidarRenderer
*/

#include "LidarWidget.h"

/*!
 * Constructs a Lidar widget. Creates the \l QLabel and \l LidarRenderer child widgets and establishes their layout within the StereoWidget widget.
 */
LidarWidget::LidarWidget(QWidget *parent) : QWidget(parent)
{
    LidarWidget::title = new QLabel(this);
    title->setText("LIDAR");
    title->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    LidarWidget::renderer = new LidarRenderer(this);
    renderer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(title);
    layout->addWidget(renderer);
    setLayout(layout);
}

/**
 * Called automatically when the widget is shown.
 * Connects the widget to the incoming data packets.
 **/
void LidarWidget::showEvent( QShowEvent* event )
{
    QWidget::showEvent( event );
    onStartReading();
}

/**
 * Called automatically when the widget is shown.
 * Disconnects the widget from the incoming data packets for better performance.
 **/
void LidarWidget::hideEvent( QHideEvent* event )
{
    QWidget::hideEvent( event );
    onStopReading();
}

void LidarWidget::onStartReading()
{
    connect(CommunicationManager::lidarThread, SIGNAL(newPacket(LidarPacket)), this, SLOT(newPacket(LidarPacket)));
}

void LidarWidget::onStopReading()
{
    disconnect(CommunicationManager::lidarThread, SIGNAL(newPacket(LidarPacket)), this, SLOT(newPacket(LidarPacket)));
}

// Called when a new packet is read
void LidarWidget::newPacket(LidarPacket packet)
{

}
