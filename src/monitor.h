#pragma once
#include <bits/stdc++.h>
#define MAX_LEN 300



class monitor
{
protected:
    std::list<int> values;

public:
    monitor(){}
    
    virtual void readData(){}
    void trimQueue();
    std::vector<int> getGraph(int width, int height);

    ~monitor() = default;
};