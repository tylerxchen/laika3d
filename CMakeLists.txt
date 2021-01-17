cmake_minimum_required(VERSION 3.19.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(laika3d)

add_subdirectory(src)

add_subdirectory(demo)

target_link_libraries(laika3d_demo laika3d)

add_subdirectory(test)

target_link_libraries(laika3d_test laika3d)
