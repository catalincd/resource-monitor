#include <bits/stdc++.h>
#define BYTES_TO_MB 1024 * 1024

int getIntLen(int i)
{
    if(i == 0)
        return 1;
        
    int l = 0;
    while(i)
    {
        i /= 10;
        l++;
    }
    return l;
}




std::string space_string_len(int i, int len)
{
    std::string str = "";
    int iLen = len - getIntLen(i);
    
    for(int t=0;t<iLen;t++)
    {
        str += " ";
    }
    return str + std::to_string(i);
}

std::string space_string(int i)
{
    return space_string_len(i, 2);
}

float BytesToMB(int64_t bytes)
{
    return (float(bytes) / BYTES_TO_MB);
}

std::string UpstreamBytes(float bytes, int precision)
{
    std::string units[] = {"B", "KiB", "MiB", "GiB", "TiB", "PiB"};
    int idx = 0;
    while(bytes > 1024.0f)
    {
        idx++;
        bytes /= 1024.0f;
    }

    std::stringstream stream;
    stream << std::fixed << std::setprecision(precision) << bytes << " " << units[idx];
    return stream.str();
}

std::string UpstreamBytes(float bytes)
{
    return UpstreamBytes(bytes, 2);
}

std::vector<std::string> Split(std::string str, char splitter)
{
    std::vector<std::string> container;

    
    size_t cursor;
    while ((cursor = str.find(splitter)) != std::string::npos)
    {
        std::string current = str.substr(0, cursor);
        if(current != "")
            container.push_back(current);
        str = str.substr(cursor + 1);
    }

    if (str != "")
        container.push_back(str);

    return container;
}

int ParseInt(std::string str)
{
    int n = 0;
    int i = 0;
    int sign = 1;

    if (str[0] == '-')
    {
        sign = -1;
        i++;
    }

    for (; i < str.length(); i++)
    {
        if(str[i] > '9' || str[i] < '0')
            return -1;
            
        n = n * 10 + (str[i] - '0');
    }

    return n * sign;
}
