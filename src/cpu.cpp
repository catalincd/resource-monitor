#include <bits/stdc++.h>
#include "util.h"
#include "cpu.h"

cpu::cpu()
{
    memset(prevIdle, 0, sizeof(prevIdle));
    memset(prevTotal, 0, sizeof(prevTotal));
}

float cpu::getUsage(std::ifstream& stream, int index)
{
    char temp[32];
    int times[10];
    int totalTime = 0;

    stream >> temp;
    if(temp[0] != 'c' || temp[1] != 'p' || temp[2] != 'u')   
        return -1.0f;


    for(int i=0;i<10;i++)
    {
        stream >> times[i];
        totalTime += times[i];
    }

    const float idleTime = times[3];
    const float idleDelta = idleTime - prevIdle[index];
    const float totalDelta = totalTime - prevTotal[index];

    prevIdle[index] = idleTime;
    prevTotal[index] = totalTime;


    return ((1.0f - (idleDelta / float(totalDelta))) * 100.0f);
}

void cpu::print()
{
    for(int i=0;i<numCPUs;i++)
    {
        std::cout<<"CPU"<<i<<" "<<coresUsage[i]<<std::endl;
    }
}

void cpu::readData()
{
    float readUsage;
    std::string temp;
    std::ifstream readStream("/proc/stat");
    numCPUs = 0;

    while((readUsage = getUsage(readStream, numCPUs)) >= 0.0f)
    {
        coresUsage[numCPUs++] = readUsage;
    }

    readStream.close();
}