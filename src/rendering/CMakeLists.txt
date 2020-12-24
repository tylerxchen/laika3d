add_library(rendering shaderutils.cpp renderer.cpp vertexbuffer.cpp indexbuffer.cpp)

find_package(GLEW REQUIRED)
target_link_libraries(rendering GLEW::GLEW)

find_package(glfw3 REQUIRED)
target_link_libraries(rendering glfw3)
