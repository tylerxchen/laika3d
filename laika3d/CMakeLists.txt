add_library(laika3d assets/indexbuffer.cpp assets/mesh.cpp assets/resourcemanager.cpp assets/shader.cpp assets/texture.cpp assets/vertexbuffer.cpp scene/geometrynode.cpp scene/transformationnode.cpp vendor/lodepng.cpp)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(PNG REQUIRED)

target_link_libraries(laika3d GLEW::GLEW OpenGL::GL glfw glm PNG::PNG)
