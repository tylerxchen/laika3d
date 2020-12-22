cmake_minimum_required(VERSION 3.19.1)

project(tc3d)

add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(math)
target_include_directories(${PROJECT_NAME} INTERFACE math)
target_link_directories(${PROJECT_NAME} PRIVATE math)

add_subdirectory(rendering)
target_link_directories(${PROJECT_NAME} PRIVATE rendering)
target_include_directories(${PROJECT_NAME} PRIVATE rendering)

target_link_libraries(${PROJECT_NAME} math rendering)
