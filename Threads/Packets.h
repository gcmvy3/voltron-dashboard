#ifndef PACKETS_H
#define PACKETS_H

#define BATTERY_PIPE_NAME "/tmp/voltron_battery"
#define CONSOLE_PIPE_NAME "/tmp/voltron_debug"

#include <QString>

struct BatteryPacket
{
    int cellNum;

    float charge;
};

struct DebugPacket
{
    int strLength;
};

struct ConsolePacket
{
    QString msg;
};

#endif
