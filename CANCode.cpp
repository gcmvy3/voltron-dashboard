#include "CANCode.h"

CANCode::CANCode(int id, QString name, int senderID, int bitStart, int bitEnd)
{
    this->id = id;
    this->name = name;
    this->senderID = senderID;
    this->bitStart = bitStart;
    this->bitEnd = bitEnd;
}

