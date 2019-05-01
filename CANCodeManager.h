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
private:
    CANCodeManager();
    static CANCodeManager* instance;

public:
    static CANCodeManager* getInstance();
    QVector<CANCode*> codes;

public slots:
    void openCANFile();
    void loadFromFile(QFile* file);

signals:
    void newCodesFileSelected(QString filePath);
    void newCodesLoaded(QVector<CANCode*> newCodes);
};

#endif // CANCODEMANAGER_H
