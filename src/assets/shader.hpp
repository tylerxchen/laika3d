#pragma once

#include "resource.hpp"

#include <string>

namespace laika3d {
  class Shader : public Resource {
    public:
      Shader(const std::string& path);
      ~Shader();

      unsigned int get_prog_id() const;
      unsigned int get_texture_id() const;
      unsigned int get_model_mat_id() const;
      unsigned int get_view_mat_id() const;
      unsigned int get_proj_mat_id() const;

      template<typename T>
      void set_uniform(unsigned int location, const T& val) const;

      unsigned int get_uniform_location(const std::string& name) const;

      void bind() const;
      void unbind() const;

    private:
      unsigned int model_uniform;
      unsigned int view_uniform;
      unsigned int proj_uniform;
      unsigned int texture_uniform;
      unsigned int vshader_id;
      unsigned int fshader_id;
      unsigned int prog_id;
  };
}
