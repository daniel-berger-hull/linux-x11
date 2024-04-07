cmake_minimum_required(VERSION 3.1)

project(x11-draw-screen2)

find_package(X11)

add_executable(x11-draw-screen2 draw-screen2.cpp)

target_link_libraries(x11-draw-screen2 ${X11_LIBRARIES})
