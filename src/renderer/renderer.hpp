#pragma once

#include "../scene/scene.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <functional>

namespace laika3d {
  class Renderer {
    public:
      Renderer(unsigned int width, unsigned int height);
      ~Renderer();

      void draw(const Scene& scene);

      void loop(std::function<void()> frame_callback);

    private:
      GLFWwindow* win;
      std::function<void()> callback;
      unsigned int vao_id;
  };
}
