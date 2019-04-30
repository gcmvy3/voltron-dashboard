#ifndef CANCODEMANAGER_H
#define CANCODEMANAGER_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QFileDialog>
#include <QVector>

#include "CommunicationManager.h"
#include "CANCode.h"

class CANCodeManager : public QObject
{
    Q_OBJECT
public:
    explicit CANCodeManager(QObject *parent = nullptr);

protected:
    static QVector<CANCode*> codes;

public slots:
    static void openCANFile();
    static void loadFromFile(QFile* file);
};

#endif // CANCODEMANAGER_H
