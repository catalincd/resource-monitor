#include <bits/stdc++.h>
#include "cpu.h"
#include "mem.h"
#include "net.h"
#include "disk.h"
#include <ftxui/screen/screen.hpp>


uint64_t STRIDE = 500; //MS


cpu g_cpu;
mem g_mem;
disk g_disk;
net g_net;

//uptime
int main(void) 
{
  const uint64_t FRAME_TIME = STRIDE * 1000; //NANO

  while(true)
  {
    system("clear");
    g_cpu.readData();
    g_cpu.print();

    g_mem.readData();
    g_mem.print();

    g_disk.readData();
    g_disk.print();

    g_net.readData();
    g_net.print();

    usleep(FRAME_TIME);
  }
  
  return EXIT_SUCCESS;
}
