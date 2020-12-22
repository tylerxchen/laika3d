#pragma once

#include <string>

namespace tc3d {
  namespace rendering {
    unsigned int compile_shader(unsigned int type, const std::string& source);
  }
}
