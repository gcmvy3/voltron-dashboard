#ifndef CANCODE_H
#define CANCODE_H

#include <QObject>

class CANCode : public QObject
{
    Q_OBJECT
public:
    CANCode(int id, QString name, QString senderIDString, int senderID, int bitStart, int bitEnd);

    int id;
    QString name;
    QString senderIDString;
    int senderID;
    int bitStart;
    int bitEnd;
};

#endif // CANCODE_H
