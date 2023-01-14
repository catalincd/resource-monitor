#pragma once
#include "sys/types.h"
#include "sys/sysinfo.h"
#include "monitor.h"
#define MAX_PARAMS 128

class mem : public monitor
{
public:
    int64_t params[MAX_PARAMS];

    int64_t totalMem;
    int64_t availMem;
    int64_t usedMem;
    float memUsage;

    int64_t totalSwap;
    int64_t availSwap;
    int64_t usedSwap;
    int64_t cachedSwap;
    float swapUsage;

    mem();

    void readData();
    void print();
};