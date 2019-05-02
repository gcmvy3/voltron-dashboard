/*!
   \class StereoWidget
   \inherits QWidget
   \brief The StereoWidget class is a custom widget which displays stereoscopic visual data obtained from shared memory.

   \ingroup voltron
   \ingroup vstereo

   This widget contains a \l StereoMemory child widget, which displays the \l QImage frames generated by \StereoMemory using data from shared memory.
   This widget creates and manages its child widgets automatically upon construction of the widget.

   \sa StereoThread, StereoMemory
*/

#include "StereoWidget.h"

/*!
 * Constructs a Stereo widget. Creates the \l QLabel and \l StereoMemory child widgets and establishes their layout within the StereoWidget widget.
 */
StereoWidget::StereoWidget(QWidget *parent) : QWidget(parent)
{
    StereoWidget::title = new QLabel(this);
    title->setText("Camera View");
    title->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);

    StereoWidget::display = new StereoMemory(this);
    display->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    display->setDisplayType(StereoMemory::DisplayType::STEREO);

    StereoWidget::typeSelector = new QComboBox(this);
    typeSelector->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
    typeSelector->addItem("Stereo", QString::number(StereoMemory::DisplayType::STEREO));
    typeSelector->addItem("Depth", QString::number(StereoMemory::DisplayType::DEPTH));
    typeSelector->setCurrentIndex(StereoMemory::DisplayType::STEREO);

    QFont font;
    font.setPointSize(font.pointSize() + 4);
    typeSelector->setFont(font);

    QHBoxLayout* hLayout = new QHBoxLayout();
    hLayout->setAlignment(Qt::AlignLeft);
    hLayout->addWidget(title);
    hLayout->addWidget(typeSelector);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addLayout(hLayout);
    layout->addWidget(display);
    setLayout(layout);

    connect(typeSelector, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(onTypeChanged()));
}

void StereoWidget::onTypeChanged()
{
    display->setDisplayType(typeSelector->currentIndex());
}
