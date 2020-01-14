#ifndef __SENSOR_DATA_H__
#define __SENSOR_DATA_H__

#define SHARE_MEM_FILE      "."

struct share_mem {
    float temperaturn;
    float humidness;
    float illumination;
    int kill_flag;
}*shm_addr;

#endif  /* sensor.h */