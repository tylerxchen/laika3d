#pragma once

#include <string>

namespace laika3d {
  class Shader {
    public:
      Shader(const std::string& vertex_path, const std::string& fragment_path);
      ~Shader();

      unsigned int get_prog_id() const { return prog_id; }
      unsigned int get_mvp_id() const { return mvp_uniform; }

      template<typename T>
      void uniform(unsigned int location, const T& val) const;

      void bind() const;
      void unbind() const;

    private:
      unsigned int mvp_uniform;
      unsigned int vshader_id;
      unsigned int fshader_id;
      unsigned int prog_id;
  };
}
