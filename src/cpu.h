#include "monitor.h"
#pragma once
#define MAX_CPUS 32

class cpu : public monitor
{
    public:
    int numCPUs = 0;
    float coresUsage[MAX_CPUS];

    float prevIdle[MAX_CPUS];
    float prevTotal[MAX_CPUS];

    cpu();

    float getUsage(std::ifstream& stream, int index);

    void readData();
    void print();

};