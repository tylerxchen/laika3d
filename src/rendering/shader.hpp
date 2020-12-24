#pragma once

#include <string>

namespace tc3d {
  namespace rendering {
    class Shader {
      public:
        Shader(const std::string& vertex_path, const std::string& fragment_path);
        ~Shader();

        void attach(unsigned int program_id);
        void detach(unsigned int program_id);

      private:
        unsigned int vshader_id;
        unsigned int fshader_id;
    };
  }
}
