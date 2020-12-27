#pragma once

#include <string>

namespace tc3d {
  namespace rendering {
    class Shader {
      public:
        Shader(const std::string& vertex_path, const std::string& fragment_path);
        ~Shader();

        unsigned int get_prog_id() const { return prog_id; }

        void bind() const;
        void unbind() const;

      private:
        unsigned int vshader_id;
        unsigned int fshader_id;
        unsigned int prog_id;
    };
  }
}
