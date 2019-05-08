/*!
   \class CANCodeManager
   \inherits QObject
   \brief The CommunicationManager class is a singleton that maintains a unified list of CANCodes. It is also used to load CAN codes from a JSON file.

   \ingroup voltron

   This class is used to load CAN codes from a JSON file and maintain a list of all current codes. See the example JSON file included in the project to learn how to format the JSON file.
*/

#include "CANCodeManager.h"
#include "SettingsManager.h"

CANCodeManager* CANCodeManager::instance = nullptr;

CANCodeManager::CANCodeManager()
{
    codes = QVector<CANCode*>();
}

/*!
 * Returns the single instance of the singleton class.
 */
CANCodeManager* CANCodeManager::getInstance()
{
    if(instance == nullptr)
    {
        instance = new CANCodeManager();
        QObject::connect(SettingsManager::getInstance(), &SettingsManager::onSettingsLoaded, instance, &CANCodeManager::loadFromFile);
        SettingsManager::getInstance()->loadSettings();
    }

    return instance;
}

/*!
 * Opens a QFileDialog for choosing a JSON file on the computer. Once a file is selected, the CAN codes defined within are loaded into the program.
 */
void CANCodeManager::openCANFile()
{
    QString fileName = QFileDialog::getOpenFileName(DashboardUtils::getMainWidget(), ("Open File"), QDir::currentPath(), ("JSON Files (*.json)"));
    if(!fileName.isNull())
    {
        QFile* file = new QFile(fileName);
        loadFromFile(file);
    }
}

/*!
 * Takes in a QFile and attempts to load CANCodes from it. The QFile should be properly formatted JSON.
 */
void CANCodeManager::loadFromFile(QFile* file)
{
    qDebug() << "Trying to load CAN codes file";

    if(file != nullptr)
    {
        qDebug() << "Found CAN codes file";

        file->open(QFile::ReadOnly);
        QJsonDocument document = QJsonDocument::fromJson(file->readAll());
        file->close();

        if(!document.isNull() || !document.isObject())
        {
            QString filePath = file->fileName();
            qDebug() << "LoadFromFile called on: " << filePath;
            emit newCodesFileSelected(filePath);

            CommunicationManager::printToConsole(QString("Loading CAN code file: ").append(QString(file->fileName())));
            QJsonObject obj = document.object();

            //Read the array of CAN codes
            QJsonArray codesArr = obj["codes"].toArray();

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
                if(!success)
                {
                    qDebug() << "ERROR: Could not convert CAN sender ID to int";
                }
                else
                {
                    int bitStart = objMap["bitStart"].toInt();
                    int bitEnd = objMap["bitEnd"].toInt();

                    CANCode* code = new CANCode(id, name, senderIDHex, senderID, bitStart, bitEnd);

                    codes.append(code);
                }
            }
            qDebug() << "Loaded CAN codes from file";
            CommunicationManager::printToConsole(QString("Loaded ").append(QString(codes.size())).append(QString( " CAN codes from file.")));
            emit newCodesLoaded(codes);
            return;
        }
    }

    CommunicationManager::printToConsole(QString("ERROR: Invalid CAN code file: ").append(QString(file->fileName())));
}
