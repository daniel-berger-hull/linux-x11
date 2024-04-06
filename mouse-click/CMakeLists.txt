cmake_minimum_required(VERSION 3.1)

project(x11-mouseclick)

find_package(X11)

add_executable(x11-window mouseclick.cpp)

target_link_libraries(x11-window ${X11_LIBRARIES})
