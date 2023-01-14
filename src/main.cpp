#include <bits/stdc++.h>
#include "cpu.h"
#include "mem.h"
#include "net.h"
#include "disk.h"
#include "renderer.h"


uint64_t STRIDE = 250; //MS
int PRECISION = 2;
int NET_PRECISION = 2;

cpu g_cpu;
mem g_mem;
disk g_disk;
net g_net;
renderer g_renderer;

//std::vector<graph*> graphs = 

int main(void) 
{
    g_renderer.init();

    return EXIT_SUCCESS;
}
