#include "renderer.h"
#include <bits/stdc++.h>
#include "cpu.h"
#include "mem.h"
#include "disk.h"
#include "net.h"
#include "util.h"

#include "../examples/dom/color_info_sorted_2d.ipp"  // for ColorInfoSorted2D
#include "ftxui/component/component.hpp"  // for Checkbox, Renderer, Horizontal, Vertical, Input, Menu, Radiobox, ResizableSplitLeft, Tab
#include "ftxui/component/component_base.hpp"  // for ComponentBase, Component
#include "ftxui/component/component_options.hpp"  // for MenuOption, InputOption
#include "ftxui/component/event.hpp"              // for Event, Event::Custom
#include "ftxui/component/screen_interactive.hpp"  // for Component, ScreenInteractive 
#include "ftxui/dom/elements.hpp"  // for text, color, operator|, bgcolor, filler, Element, vbox, size, hbox, separator, flex, window, graph, EQUAL, paragraph, WIDTH, hcenter, Elements, bold, vscroll_indicator, HEIGHT, flexbox, hflow, border, frame, flex_grow, gauge, paragraphAlignCenter, paragraphAlignJustify, paragraphAlignLeft, paragraphAlignRight, dim, spinner, LESS_THAN, center, yframe, GREATER_THAN
#include "ftxui/dom/flexbox_config.hpp"  // for FlexboxConfig
#include "ftxui/screen/color.hpp"  // for Color, Color::BlueLight, Color::RedLight, Color::Black, Color::Blue, Color::Cyan, Color::CyanLight, Color::GrayDark, Color::GrayLight, Color::Green, Color::GreenLight, Color::Magenta, Color::MagentaLight, Color::Red, Color::White, Color::Yellow, Color::YellowLight, Color::Default, Color::Palette256, ftxui
#include "ftxui/screen/color_info.hpp"  // for ColorInfo
#include "ftxui/screen/terminal.hpp"    // for Size, Dimensions
#include "ftxui/screen/screen.hpp"    // for Size, Dimensions
#include "ftxui/dom/node.hpp"

using namespace ftxui;
extern uint64_t STRIDE;
extern cpu g_cpu;
extern mem g_mem;
extern net g_net;
extern disk g_disk;



void renderer::init()
{
    
    auto screen = ScreenInteractive::Fullscreen();
    screen.SetCursor((Screen::Cursor){0});

    auto cpu_graph = [&](int width, int height) {
    return g_cpu.getGraph(width, height);
    };

    auto ram_graph = [&](int width, int height) {
    return g_mem.getGraph(width, height);
    };

    auto net_graph_down = [&](int width, int height) {
    std::vector<int> values = g_net.getGraph(width, 1000);

    for(int i=0;i<values.size();++i)
    {
        values[i] /= 100000; 

        if(values[i] < 0)
            values[i] = 100;

        values[i] = float(values[i]) / 100.0f * float(height);
    }

    return values;
    };

    auto net_graph_up = [&](int width, int height) {
    std::vector<int> values = g_net.getGraph(width, 1000);

    for(int i=0;i<values.size();++i)
    {
        values[i] -= values[i] / 100000;
        values[i] /= 10; 

        if(values[i] < 0)
            values[i] = 100;

        values[i] = float(values[i]) / 100.0f * float(height);
    }

    return values;
    };


    auto htop = Renderer([&] {
    auto cpubox =
        window(text("CPU %") | hcenter | bold,
            hbox({
                vbox({
                    text("100 "),
                    filler(),
                    text("75 "),
                    filler(),
                    text("50 "),
                    filler(),
                    text("25 "),
                    filler(),
                    text("0 "),
                }),
                graph(std::ref(cpu_graph)) | flex | color(Color::BlueLight),
            }) | flex);

    auto rambox =
        window(text("RAM %") | hcenter | bold,
            hbox({
                vbox({
                    text("100 "),
                    filler(),
                    text("75 "),
                    filler(),
                    text("50 "),
                    filler(),
                    text("25 "),
                    filler(),
                    text("0 "),
                }),
                graph(std::ref(ram_graph)) | flex | color(Color::Green),
            }) | flex);

    auto netbox =
        window(text("Network [MiB/s] [UP/DOWN]") | hcenter | bold,
            vbox({
                hbox({
                vbox({
                    text("50 "),
                    filler(),
                    text("25 "),
                    filler(),
                    text("0 "),
                }),
                graph(std::ref(net_graph_up)) | flex | color(Color::Purple),
            }) | flex,
            hbox({
                vbox({
                    text("50 "),
                    filler(),
                    text("25 "),
                    filler(),
                    text("0 "),
                }),
                graph(std::ref(net_graph_down)) | flex | color(Color::Purple),
            }) | flex
            }));

    Elements content;
    content.push_back(filler());
    for(int i=1;i<g_cpu.numCPUs;i++)
    {
        content.push_back(text("CPU" + space_string(i) + ": " + space_string_len(int(g_cpu.coresUsage[i]), 3)) | hcenter | color(Color::Red));
    }
    content.push_back(filler());

    auto cpu_list = window(text("CPU CORES %") | bold,
            hbox({
                vbox(std::move(content)),
        }));

    std::string ramus = "" + std::to_string(int(g_mem.memUsage)) + "%";
    auto ram_list = window(text("Swap %") | hcenter | bold,
            hbox({
                filler(),
                vbox(
                    filler(),
                    text("") | hcenter,
                    filler(),
                    text(ramus) | hcenter | color(Color::Red),
                    filler(),
                    text("") | hcenter,
                    filler()
                ),
                filler(),
        }));

    std::string swapus = "" + std::to_string(int(g_mem.swapUsage)) + "%";
    auto swap_list = window(text("Swap %") | hcenter | bold,
            hbox({
                filler(),
                vbox(
                    filler(),
                    text("") | hcenter,
                    filler(),
                    text(swapus) | hcenter | color(Color::Red),
                    filler(),
                    text("") | hcenter,
                    filler()
                ),
                filler(),
        }));

    std::string du = "" + std::to_string(int(g_disk.diskUsage)) + "%";
    auto hdd_list = window(text("DISK %") | hcenter | bold,
            hbox({
                filler(),
                vbox(
                    filler(),
                    text("") | hcenter,
                    filler(),
                    text(du) | hcenter | color(Color::Red),
                    filler(),
                    text("") | hcenter,
                    filler()
                ),
                filler(),
        }));

    

    return hbox({
                vbox({
                    cpubox | flex,
                    rambox | flex,
                    netbox | flex,
                }) | flex,
                vbox({
                    cpu_list | flex,
                    ram_list | flex,
                    swap_list | flex,
                    hdd_list | flex,
                }),
            }) | flex;
    });



    std::atomic<bool> refresh_ui_continue = true;
    std::thread refresh_ui([&] {
    while (refresh_ui_continue) {
        using namespace std::chrono_literals;
        usleep(1000 * STRIDE);

        g_cpu.readData();
        g_mem.readData();
        g_net.readData();
        g_disk.readData();

        //screen.Post([&] { shift++; });
        screen.Post(Event::Custom);
    }
    });

    screen.Loop(htop);
    refresh_ui_continue = false;
    refresh_ui.join();
}