#ifndef __SENSOR_DATA_H__
#define __SENSOR_DATA_H__

#define SHARE_MEM_FILE      "./share_mem_file"

struct share_mem {
    int pid_r;
    int pid_w;
    float temperaturn;
    float humidness;
    float illumination;
    int kill_flag;
}*shm_addr;

#endif  /* sensor.h */