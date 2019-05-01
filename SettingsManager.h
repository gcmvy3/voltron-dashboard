#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QObject>
#include <QFile>

class SettingsManager : public QObject
{
    Q_OBJECT
public:
    static SettingsManager* getInstance();
    QString getFileName(){return QString("settings.json");}

private:
    SettingsManager();
    static SettingsManager* instance;
    QFile* settingsFile;
    QString canCodesFilePath;

signals:
    void onSettingsLoaded(QFile* settingsFile);

public slots:
    void onNewCANCodesFile(QString filePath);
    void saveSettings();
    void loadSettings();
};

#endif // SETTINGSMANAGER_H
