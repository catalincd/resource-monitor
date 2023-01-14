cmake_minimum_required (VERSION 3.11)
 
# --- Fetch FTXUI --------------------------------------------------------------
include(FetchContent)
 
set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
)
 
FetchContent_GetProperties(ftxui)
if(NOT ftxui_POPULATED)
  FetchContent_Populate(ftxui)
  add_subdirectory(${ftxui_SOURCE_DIR} ${ftxui_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()
 
# ------------------------------------------------------------------------------
 
project(resource-monitor
  LANGUAGES CXX
  VERSION 1.0.0
)
 
add_executable(resource-monitor 
  src/main.cpp
  src/monitor.cpp
  src/renderer.cpp
  src/net.cpp
  src/disk.cpp
  src/mem.cpp
  src/util.cpp
  src/cpu.cpp)
target_include_directories(resource-monitor PRIVATE src)
 
target_link_libraries(resource-monitor
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component
)
