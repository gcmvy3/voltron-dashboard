#ifndef PLUGINWIDGET_H
#define PLUGINWIDGET_H

#include <QWidget>

namespace Ui {
class PluginWidget;
}

class PluginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PluginWidget(QWidget *parent = nullptr);
    ~PluginWidget();

private:
    Ui::PluginWidget *ui;

signals:

public slots:
    void testSlot();
};

#endif // PLUGINWIDGET_H
