#ifndef PACKETS_H
#define PACKETS_H

#define BATTERY_PIPE_NAME "/tmp/voltron_battery"
#define CONSOLE_PIPE_NAME "/tmp/voltron_console"

#include <QString>

struct BatteryPacket
{
    int cellNum;

    float charge;
};

struct ConsolePacket
{
    int stringSize;

    QString msg;
};

#endif
