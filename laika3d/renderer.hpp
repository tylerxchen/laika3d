#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "vertexbuffer.hpp"
#include "indexbuffer.hpp"
#include "shader.hpp"
#include "model.hpp"

namespace laika3d {
  void GLAPIENTRY message_callback(GLenum source, GLenum type, GLuint id, GLenum severity,
                                    GLsizei length, const GLchar* message, const void* userParam);

  class Renderer {
    public:
      Renderer();

      void draw(const Model& m, const Shader& s) const;

    private:
      GLFWwindow* window;
      unsigned int vao_id;
  };
}
