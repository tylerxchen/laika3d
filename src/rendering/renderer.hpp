#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "vertexbuffer.hpp"
#include "indexbuffer.hpp"

namespace tc3d {
  namespace rendering {
    class Renderer {
      public:
        Renderer();

        void draw(const VertexBuffer& vbuf, const IndexBuffer& ibuff) const;

      private:
        GLFWwindow* window;
        unsigned int vao_id;
    };
  }
}
