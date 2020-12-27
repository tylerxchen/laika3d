#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <functional>

namespace laika3d {
  class Window {
    public:
      Window();
      ~Window();

      void set_callback(const std::function<void()>& cb) { callback = cb; }
      void loop();
    private:
      GLFWwindow* win;
      std::function<void()> callback;
  };
}