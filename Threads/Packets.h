#ifndef PACKETS_H
#define PACKETS_H

#define MULTICAST_GROUP "224.0.0.155"

#define DEBUG_PORT 12000
#define BATTERY_PORT 12001
#define LIDAR_PORT 12002
#define CAN_CONTROL_PORT 12003
#define CAN_DATA_PORT 12004
#define LOGGING_CONTROL_PORT 12005
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
    char data[8];
};

struct CANControlPacket
{
    int id;
    int sender;
};

#define LIDAR_MEMORY_NAME "/voltron_lidar_data"

#define LIDAR_DATA_NUM_POINTS 384 * 75
//910 * 16 * 2
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

#define CAM_MEMORY_NAME "/voltron_camera_data"

#define CAM_WIDTH 1280
#define CAM_HEIGHT 720
#define CAM_NUM_IMAGES 4

struct StereoData
{
    char rgbImage[CAM_WIDTH * 2][CAM_HEIGHT][4];
    float depth[CAM_WIDTH][CAM_HEIGHT];
};

struct StereoPacket
{
    int updated;
};

enum LoggingControlCode
{
    Shutdown = 0,
    StartDrive = 1,
    EndDrive = 2,
    StartBatteryCapture = 3,
    EndBatteryCapture = 4,
    StartCANCapture = 5,
    EndCANCapture = 6,
    StartLIDARCapture = 7,
    EndLIDARCapture = 8,
    StartGPSCapture = 9,
    EndGPSCapture = 10,
    StartZEDCapture = 11,
    EndZEDCapture = 12
};

struct LoggingControlPacket
{
    enum LoggingControlCode code;
};

#endif
