#include <bits/stdc++.h>
#include "cpu.h"
#include <ftxui/screen/screen.hpp>


cpu g_cpu;

int main(void) 
{
  while(true)
  {
    system("clear");
    g_cpu.readData();
    g_cpu.print();
    sleep(1);
  }
  
  return EXIT_SUCCESS;
}
