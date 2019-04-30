#include "CANCode.h"

CANCode::CANCode(int id, QString name, QString senderIDString, int senderID, int bitStart, int bitEnd)
{
    this->id = id;
    this->name = name;
    this->senderIDString = senderIDString;
    this->senderID = senderID;
    this->bitStart = bitStart;
    this->bitEnd = bitEnd;
}

