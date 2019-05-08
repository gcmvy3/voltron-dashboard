#include "SettingsManager.h"
#include "CANCodeManager.h"

SettingsManager* SettingsManager::instance = nullptr;

SettingsManager::SettingsManager()
{
    SettingsManager::settingsFile = nullptr;
    SettingsManager::canCodesFilePath = nullptr;
}

void SettingsManager::onNewCANCodesFile(QString filePath)
{
    canCodesFilePath = filePath;
    qDebug() << "Setting canCodesFilePath to " << filePath;
    saveSettings();
}

void SettingsManager::saveSettings()
{
    QString filePath = QDir::currentPath().append("/").append(SettingsManager::getFileName());

    QFile* settingsFile = new QFile(filePath);

    qDebug() << "Saving settings to " << filePath;

    QJsonObject obj;
    if(canCodesFilePath == nullptr)
    {
        canCodesFilePath = QString("");
    }
    qDebug() << "CAN codes file path: " << canCodesFilePath;

    obj.insert("CAN Codes File Path", QJsonValue::fromVariant(canCodesFilePath));

    QJsonDocument doc(obj);

    // Creates the file if it doesn't exist
    settingsFile->open(QIODevice::WriteOnly);
    settingsFile->write(doc.toJson());
    settingsFile->close();
};

SettingsManager* SettingsManager::getInstance()
{
    if(instance == nullptr)
    {
        instance = new SettingsManager();
        QObject::connect(CANCodeManager::getInstance(), &CANCodeManager::newCodesFileSelected, instance, &SettingsManager::onNewCANCodesFile);
        instance->loadSettings();
    }
    return instance;
}

void SettingsManager::loadSettings()
{
    qDebug() << "Loading settings";

    QString filePath = QDir::currentPath().append("/").append(SettingsManager::getFileName());

    QFile* settingsFile = new QFile(filePath);
    if(settingsFile != nullptr)
    {
        // If the settings file doesn't exist, create it
        if(!settingsFile->exists())
        {
            qDebug() << "Trying to create settings file";
            saveSettings();
        }

        // Load settings from the file
        settingsFile->open(QIODevice::ReadOnly);
        QJsonDocument document = QJsonDocument::fromJson(settingsFile->readAll());
        settingsFile->close();
        if(!document.isNull() || !document.isObject())
        {
            QJsonObject obj = document.object();
            if(obj.contains("CAN Codes File Path"))
            {
                canCodesFilePath = obj.value("CAN Codes File Path").toString();
                qDebug() << "Found file path " << canCodesFilePath;
            }
            else
            {
                canCodesFilePath = QString("");
            }

            emit onSettingsLoaded(settingsFile);
            return;
        }
    }
    qDebug() << "ERROR: Could not load settings file";
}
