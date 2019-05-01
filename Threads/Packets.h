#ifndef PACKETS_H
#define PACKETS_H

#define CONSOLE_PORT 12000
#define BATTERY_PORT 12001
#define LIDAR_PORT 12002
#define CAN_CONTROL_PORT 12003
#define CAN_DATA_PORT 12004
#define STEREO_PORT 12006

#include <string>
#define DEBUG_MAX_LENGTH 1024

struct DebugPacket
{
    int strLength;
    char str[DEBUG_MAX_LENGTH];
};

struct BatteryPacket
{
    int cellNum;

    float charge;
};

struct CANDataPacket
{
    int id;
    int sender;
    unsigned char data[8];
};

struct CANControlPacket
{
    int id;
    int sender;
};

#define LIDAR_MEMORY_NAME "/voltron_lidar_data"

#define LIDAR_DATA_NUM_POINTS 910 * 16 * 2
#define LIDAR_DATA_NUM_REGIONS 4

struct LIDARData
{
    struct
    {
        float x;
        float y;
        float z;
        float reflectivity;
    } point[LIDAR_DATA_NUM_POINTS];
};

struct LidarPacket
{
    int updated;
};

#define STEREO_MEMORY_NAME "/voltron_stereo_data"
#define STEREO_DATA_NUM_REGIONS 4

struct StereoData
{
    //Needs to be defined
    u_char *data;
};

struct StereoPacket
{
    int updated;
};

#endif
