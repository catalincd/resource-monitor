#pragma once
#include <cstdint>

class disk
{
public:
    int64_t size;
    int64_t avail;
    float diskUsage;

    disk();

    void readData();
    void print();
};