add_library(rendering shaderutils.cpp renderer.cpp vertexbuffer.cpp indexbuffer.cpp window.cpp)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)

target_link_libraries(rendering GLEW::GLEW OpenGL::GL glfw)
