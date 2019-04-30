#ifndef CANWIDGET_H
#define CANWIDGET_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QPushButton>
#include "DashboardUtils.h"
#include "CANCodeManager.h"

class CANWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CANWidget(QWidget *parent = nullptr);

protected:
    void showEvent( QShowEvent* event) override;

    int widgetIndex = -1;
    QPushButton* loadCANFileButton;

signals:

public slots:
};

#endif // CANWIDGET_H
