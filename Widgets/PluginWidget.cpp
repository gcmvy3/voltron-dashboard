#include "PluginWidget.h"
#include "ui_PluginWidget.h"

PluginWidget::PluginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PluginWidget)
{
    ui->setupUi(this);
}

PluginWidget::~PluginWidget()
{
    delete ui;
}
