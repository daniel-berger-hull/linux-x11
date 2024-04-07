cmake_minimum_required(VERSION 3.1)

project(x11-draw-screen)

find_package(X11)

add_executable(x11-draw-screen draw-screen.cpp)

target_link_libraries(x11-draw-screen ${X11_LIBRARIES})
