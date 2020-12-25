#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "vertexbuffer.hpp"
#include "indexbuffer.hpp"
#include "shader.hpp"

namespace tc3d {
  namespace rendering {
    void GLAPIENTRY message_callback(GLenum source, GLenum type, GLuint id, GLenum severity,
                                     GLsizei length, const GLchar* message, const void* userParam);

    class Renderer {
      public:
        Renderer();

        void use_program(unsigned int prog_id) const;

        void draw(const VertexBuffer& vbuf, const IndexBuffer& ibuff, const Shader& s) const;

      private:
        GLFWwindow* window;
        unsigned int vao_id;
    };
  }
}
