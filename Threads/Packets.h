#ifndef PACKETS_H
#define PACKETS_H

#define CONSOLE_PORT 12000
#define BATTERY_PORT 12001

#define STEREO_PORT 12003

struct ConsolePacket
{
    int strLength;
};

struct BatteryPacket
{
    int cellNum;

    float charge;
};


#define LIDAR_MEMORY_NAME "/voltron_lidar_data"

#define LIDAR_DATA_NUM_POINTS 384 * 16
#define LIDAR_DATA_NUM_REGIONS 8

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

struct StereoPacket
{

};

#endif
