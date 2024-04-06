cmake_minimum_required(VERSION 3.1)

project(x11-drawing)

find_package(X11)

add_executable(x11-drawing windrawing.cpp)

target_link_libraries(x11-drawing ${X11_LIBRARIES})
