#ifndef CANWIDGET_H
#define CANWIDGET_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>

class CANWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CANWidget(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // CANWIDGET_H