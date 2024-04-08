cmake_minimum_required(VERSION 3.1)

project(x11-draw-linear-gradient)

find_package(X11)

add_executable(x11-draw-linear-gradient draw-linear-gradient.cpp)

target_link_libraries(x11-draw-linear-gradient ${X11_LIBRARIES})
