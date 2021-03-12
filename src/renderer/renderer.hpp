#pragma once

#include "../scene/scene.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../vendor/dear_imgui/imgui.h"
#include "../vendor/dear_imgui/imgui_impl_glfw.h"
#include "../vendor/dear_imgui/imgui_impl_opengl3.h"

#include <functional>

namespace laika3d {
  class Renderer {
    public:
      Renderer(unsigned int width, unsigned int height);
      ~Renderer();

      void draw(const Scene& scene);

      void set_key_callback(void (*key_callback)(GLFWwindow*, int, int, int, int));

      void loop(std::function<void()> frame_callback);

      struct RenderStats {
        unsigned int vertices;
        unsigned int indices;
      } stats;

    private:
      enum AttributeIndex : unsigned int {
        VERTEX_POSITION = 0,
        VERTEX_NORMAL = 1,
        TEXTURE_COORDINATE = 2,
      };

      void draw_impl(const Scene& scene, std::shared_ptr<SceneNode> root, glm::mat4& state);
      void setup_buffers();

      GLFWwindow* win;
      std::function<void()> callback;
      unsigned int vao_id;
  };
}
