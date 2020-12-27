cmake_minimum_required(VERSION 3.19.1)

project(tc3d)

add_executable(tc3d_demo demo.cpp)

add_subdirectory(tc3d)
target_link_directories(tc3d_demo PRIVATE tc3d)
target_include_directories(tc3d_demo PRIVATE tc3d)

target_link_libraries(tc3d_demo tc3d)
