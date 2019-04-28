#include "CANCodeManager.h"

CANCodeManager::CANCodeManager(QObject *parent) : QObject(parent)
{

}

void CANCodeManager::loadFromFile(QFile* file)
{
    file->open(QFile::ReadOnly);
    QJsonDocument document = QJsonDocument::fromJson(file->readAll());
    if(!document.isNull())
    {
        CommunicationManager::printToConsole(QString("Successfully loaded CAN code file: ").append(QString(file->fileName())));
    }
    else
    {
        CommunicationManager::printToConsole(QString("ERROR: Invalid CAN code file: ").append(QString(file->fileName())));
    }
}
