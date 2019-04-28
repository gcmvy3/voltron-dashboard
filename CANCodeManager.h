#ifndef CANCODEMANAGER_H
#define CANCODEMANAGER_H

#include <QObject>
#include <QJsonDocument>
#include <QFileDialog>

#include "CommunicationManager.h"

class CANCodeManager : public QObject
{
    Q_OBJECT
public:
    explicit CANCodeManager(QObject *parent = nullptr);
    QJsonDocument canCodesDocument;

public slots:
    static void loadFromFile(QFile* file);
};

#endif // CANCODEMANAGER_H
