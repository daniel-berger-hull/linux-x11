cmake_minimum_required(VERSION 3.1)

project(x11-window)

find_package(X11)

add_executable(x11-window main.cpp)

target_link_libraries(x11-window ${X11_LIBRARIES})
