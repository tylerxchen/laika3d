set(
  SOURCES
  # header files
  assets/indexbuffer.hpp
  assets/mesh.hpp
  assets/resource.hpp
  assets/resourcemanager.hpp
  assets/shader.hpp
  assets/texture.hpp
  assets/vertexbuffer.hpp
  renderer/renderer.hpp
  scene/geometrynode.hpp
  scene/scene.hpp
  scene/camera.hpp
  scene/scenenode.hpp
  scene/transformationnode.hpp
  vendor/lodepng.h
  # source files
  assets/indexbuffer.cpp
  assets/mesh.cpp
  assets/resourcemanager.cpp
  assets/shader.cpp
  assets/texture.cpp
  assets/vertexbuffer.cpp
  renderer/renderer.cpp
  scene/geometrynode.cpp
  scene/scene.cpp
  scene/camera.cpp
  scene/transformationnode.cpp
  vendor/lodepng.cpp
)

add_library(laika3d ${SOURCES})

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

target_link_libraries(laika3d GLEW::GLEW OpenGL::GL glfw glm)
