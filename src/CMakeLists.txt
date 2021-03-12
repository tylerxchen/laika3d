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
  assets/material_presets.hpp
  assets/material.hpp
  renderer/renderer.hpp
  scene/geometrynode.hpp
  scene/scene.hpp
  scene/camera.hpp
  scene/scenenode.hpp
  scene/transformationnode.hpp
  scene/pointlight.hpp
  vendor/lodepng/lodepng.h
  vendor/dear_imgui/imconfig.h
  vendor/dear_imgui/imgui_impl_glfw.h
  vendor/dear_imgui/imgui_impl_opengl3.h
  vendor/dear_imgui/imgui_internal.h
  vendor/dear_imgui/imgui.h
  vendor/dear_imgui/imstb_rectpack.h
  vendor/dear_imgui/imstb_textedit.h
  vendor/dear_imgui/imstb_truetype.h
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
  vendor/lodepng/lodepng.cpp
  vendor/dear_imgui/imgui_demo.cpp
  vendor/dear_imgui/imgui_draw.cpp
  vendor/dear_imgui/imgui_impl_glfw.cpp
  vendor/dear_imgui/imgui_impl_opengl3.cpp
  vendor/dear_imgui/imgui_tables.cpp
  vendor/dear_imgui/imgui_widgets.cpp
  vendor/dear_imgui/imgui.cpp
)

add_library(laika3d ${SOURCES})

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

target_link_libraries(laika3d GLEW::GLEW OpenGL::GL glfw glm)
