#pragma once

#include "resource.hpp"

#include <string>

namespace laika3d {
  class Shader : public Resource {
    public:
      Shader(const std::string& vertex_path, const std::string& fragment_path);
      ~Shader();

      unsigned int get_prog_id() const;
      unsigned int get_mvp_id() const;

      template<typename T>
      void set_uniform(unsigned int location, const T& val) const;

      unsigned int get_uniform_location(const std::string& name) const;

      void bind() const;
      void unbind() const;

    private:
      unsigned int mvp_uniform;
      unsigned int vshader_id;
      unsigned int fshader_id;
      unsigned int prog_id;
  };
}
