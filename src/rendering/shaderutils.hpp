#pragma once

#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace tc3d {
  namespace rendering {
    unsigned int load_shaders(const std::string& vertex_path, const std::string& fragment_path);
  }
}
