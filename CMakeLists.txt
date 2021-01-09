cmake_minimum_required(VERSION 3.19.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(laika3d)

add_subdirectory(demo)

add_subdirectory(laika3d)
target_link_directories(laika3d_demo PRIVATE laika3d)
target_include_directories(laika3d_demo PRIVATE laika3d laika3d/vendor)

target_link_libraries(laika3d_demo laika3d)
