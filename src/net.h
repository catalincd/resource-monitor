#pragma once
#include <cstdint>

class net
{
public:
    int64_t totalBytesUp;
    int64_t deltaBytesUp;
    float speedBytesUp;

    int64_t totalBytesDown;
    int64_t deltaBytesDown;
    float speedBytesDown;

    net();

    void readData();
    void print();
};