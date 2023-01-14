#include "monitor.h"


void monitor::trimQueue()
{
    while(values.size() > MAX_LEN)
    {
        values.pop_front();
    }
}

std::vector<int> monitor::getGraph(int width, int height) {
    std::vector<int> output(width, 0);
    std::list<int>::reverse_iterator it = values.rbegin();
    
    for(int i=width;i > 0 && it != values.rend();++it)
    {
        output[--i] = float(*it) / 100.0f * float(height);
    }

    return output;
}