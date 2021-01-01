add_library(laika3d shader.cpp renderer.cpp vertexbuffer.cpp indexbuffer.cpp model.cpp camera.cpp vendor/lodepng.cpp)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(PNG REQUIRED)

target_link_libraries(laika3d GLEW::GLEW OpenGL::GL glfw glm PNG::PNG)
