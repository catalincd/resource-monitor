#include <sys/statvfs.h>
#include <iostream>
#include "disk.h"

disk::disk()
{

}

void disk::readData()
{
    int fd;
    struct statvfs stats;

    statvfs("/", &stats);


    avail = stats.f_bavail * stats.f_bsize;
    size = stats.f_blocks * stats.f_bsize;

    diskUsage = 100.0f * (1.0f - (float(avail) / float(size)));
}

void disk::print()
{
    std::cout<<"DU:\t"<<diskUsage<<std::endl;
}