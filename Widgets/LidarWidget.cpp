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

    zoomSlider = new QSlider(this);
    zoomSlider->setOrientation(Qt::Vertical);
    zoomSlider->setStyleSheet(".QSlider::handle:vertical {width: 23px;height: 100px;}");

    QHBoxLayout* hLayout = new QHBoxLayout();
    hLayout->addWidget(renderer);
    hLayout->addWidget(zoomSlider);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(title);
    layout->addLayout(hLayout);
    setLayout(layout);
}

