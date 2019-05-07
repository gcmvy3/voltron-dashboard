/*!
   \class CANCode
   \inherits QObject
   \brief A CANCode object represents a type of packet being sent over the vehicle's CAN bus. These packets are defined in a JSON file that is loaded by CANCodeManager.

   \ingroup voltron
*/

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

