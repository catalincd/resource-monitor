#pragma once
#define MAX_CPUS 32

class cpu
{
    public:
    int numCPUs = 0;
    float coresUsage[MAX_CPUS];

    float prevIdle[MAX_CPUS];
    float prevTotal[MAX_CPUS];

    cpu() 
    {
        memset(prevIdle, 0, sizeof(prevIdle));
        memset(prevTotal, 0, sizeof(prevTotal));
    }

    float getUsage(std::ifstream& stream, int index);

    void readData();
    void print();

};