#include <bits/stdc++.h>
#include "net.h"
#define BYTES_TO_MB 1024 * 1024

extern uint64_t STRIDE;

net::net()
{
    totalBytesDown = 0;
    totalBytesUp = 0;
}

void net::readData()
{
    std::string temp;
    std::string interface;
    std::ifstream readStream("/proc/net/dev");
    int64_t data[16];
    
    getline(readStream, temp);
    getline(readStream, temp);
    getline(readStream, temp);
    readStream.get();

    int64_t currentBytesDown = 0;
    int64_t currentBytesUp = 0;
    while(readStream>>interface)
    {
        for(int i=0;i<16;++i)
        {
            readStream>>data[i];
        }
        currentBytesDown += data[0];
        currentBytesUp += data[8];
    }

    deltaBytesDown = currentBytesDown - totalBytesDown;
    deltaBytesUp = currentBytesUp - totalBytesUp;

    totalBytesDown = currentBytesDown;
    totalBytesUp = currentBytesUp;


    const float speedFactor = (1000.0f / (1.0f * STRIDE));
    speedBytesDown = speedFactor * deltaBytesDown;
    speedBytesUp = speedFactor * deltaBytesUp;

    readStream.close();
}

void net::print()
{
    std::cout<<"TOTAL DOWN:\t"<<(totalBytesDown / (1LL * BYTES_TO_MB))<<"MiB"<<std::endl;
    std::cout<<"TOTAL UP:\t"<<(totalBytesUp / (1LL * BYTES_TO_MB))<<"MiB"<<std::endl;
    std::cout<<"SPEED DOWN:\t"<<(speedBytesDown / (1LL * BYTES_TO_MB))<<"MiB/s"<<std::endl;
    std::cout<<"SPEED UP:\t"<<(speedBytesUp / (1LL * BYTES_TO_MB))<<"MiB/s"<<std::endl;
}