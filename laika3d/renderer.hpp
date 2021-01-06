#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <functional>

#include "vertexbuffer.hpp"
#include "indexbuffer.hpp"
#include "shader.hpp"
#include "model.hpp"
#include "camera.hpp"

namespace laika3d {
  void GLAPIENTRY message_callback(GLenum source, GLenum type, GLuint id, GLenum severity,
                                   GLsizei length, const GLchar* message, const void* userParam);
  
  enum AttributeIndex : unsigned int {
    VERTEX_POSITION = 0,
    TEXTURE_COORDINATE = 1,
    VERTEX_NORMAL = 2,
  };

  class Renderer {
    public:
      Renderer(unsigned int width, unsigned int height);
      ~Renderer();

      void set_callback(const std::function<void()>& cb) { callback = cb; }
      void loop();

      void draw(const Model& m, const Shader& s, const Camera& c);

    private:
      glm::mat4 mvp;
      GLFWwindow* win;
      std::function<void()> callback;
      unsigned int vao_id;
  };
}
