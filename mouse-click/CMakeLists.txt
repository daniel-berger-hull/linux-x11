cmake_minimum_required(VERSION 3.1)

project(x11-mouseclick)

find_package(X11)

add_executable(x11-mouseclick mouseclick.cpp)

target_link_libraries(x11-mouseclick ${X11_LIBRARIES})
