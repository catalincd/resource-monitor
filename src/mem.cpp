#include <bits/stdc++.h>
#include "mem.h"
#define MB_FACTOR 1024
#define GB_FACTOR 1024*1024

mem::mem()
{

}

void mem::readData()
{
    std::string paramName;
    std::string junkKiB;
    std::ifstream readStream("/proc/meminfo");

    for(int i=0;readStream>>paramName;)
    {
        readStream>>params[i++];
        readStream>>junkKiB;
    }

    totalMem = params[0];
    availMem = params[2];
    usedMem = totalMem - availMem;
    memUsage = 100.0f * (float(usedMem) / float(totalMem));

    totalSwap = params[14];
    availSwap = params[15];
    cachedSwap = 0;
    usedSwap = totalSwap - (availSwap + cachedSwap);
    swapUsage = 100.0f * (float(usedSwap) / float(totalSwap? totalSwap:1));

    readStream.close();
}

void mem::print()
{
    std::cout<<"RAM:\t"<<std::fixed<<std::setprecision(3)<<memUsage<<std::endl;
    std::cout<<"SWAP:\t"<<std::fixed<<std::setprecision(3)<<swapUsage<<std::endl;
}