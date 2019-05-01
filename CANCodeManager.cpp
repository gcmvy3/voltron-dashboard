#include "CANCodeManager.h"

CANCodeManager* CANCodeManager::instance = new CANCodeManager();

CANCodeManager::CANCodeManager()
{
    codes = QVector<CANCode*>();
}

CANCodeManager* CANCodeManager::getInstance()
{
    return instance;
}

void CANCodeManager::openCANFile()
{
    QString fileName = QFileDialog::getOpenFileName(nullptr, ("Open File"), QDir::currentPath(), ("JSON Files (*.json)"));
    if(!fileName.isNull())
    {
        QFile* file = new QFile(fileName);
        loadFromFile(file);
    }
}

void CANCodeManager::loadFromFile(QFile* file)
{
    file->open(QFile::ReadOnly);
    QJsonDocument document = QJsonDocument::fromJson(file->readAll());
    file->close();

    if(!document.isNull() || !document.isObject())
    {
        CommunicationManager::printToConsole(QString("Loading CAN code file: ").append(QString(file->fileName())));
        QJsonObject obj = document.object();

        //Read the array of CAN codes
        QJsonArray codesArr = obj["codes"].toArray();

        //codes = new QVector<CANCode*>(codesArr.size());

        //For each code, parse it into a CANCode object
        for(int i = 0; i < codesArr.size(); i++)
        {
            QJsonObject codeObj = codesArr[i].toObject();
            QVariantMap objMap = codeObj.toVariantMap();
            int id = i;

            QString name = objMap["name"].toString();

            QString senderIDHex = objMap["senderID"].toString();
            bool success;
            int senderID = senderIDHex.toInt(&success, 16);

            int bitStart = objMap["bitStart"].toInt();
            int bitEnd = objMap["bitEnd"].toInt();

            CANCode* code = new CANCode(id, name, senderIDHex, senderID, bitStart, bitEnd);

            codes.append(code);
        }
        CommunicationManager::printToConsole(QString("Loaded ").append(QString(codes.size())).append(QString( " CAN codes from file.")));
        emit newCodesLoaded(codes);
    }

    CommunicationManager::printToConsole(QString("ERROR: Invalid CAN code file: ").append(QString(file->fileName())));
}
