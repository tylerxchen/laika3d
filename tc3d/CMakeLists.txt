add_library(tc3d shader.cpp renderer.cpp vertexbuffer.cpp indexbuffer.cpp window.cpp model.cpp)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

target_link_libraries(tc3d GLEW::GLEW OpenGL::GL glfw glm)
