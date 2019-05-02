#ifndef DASHBOARDUTILS_H
#define DASHBOARDUTILS_H

#include <QObject>
#include <QWidget>

class DashboardUtils : public QObject
{
    Q_OBJECT
public:
    explicit DashboardUtils(QObject *parent = 0);
    static int getWidgetIndex(QWidget* widget);

signals:

public slots:
};

#endif // DASHBOARDUTILS_H
