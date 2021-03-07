#pragma once

#include "resource.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

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
      unsigned int get_ambient_id() const;
      unsigned int get_diffuse_id() const;
      unsigned int get_specular_id() const;
      unsigned int get_shininess_id() const;

      template<typename T>
      void set_uniform(unsigned int location, const T& val) const {
        if constexpr (std::is_same<T, float>::value) {
          glUniform1f(location, val);
        }
        else if constexpr (std::is_same<T, glm::vec2>::value) {
          glUniform2f(location, val[0], val[1]);
        }
        else if constexpr (std::is_same<T, glm::vec3>::value) {
          glUniform3f(location, val[0], val[1], val[2]);
        }
        else if constexpr (std::is_same<T, glm::vec4>::value) {
          glUniform4f(location, val[0], val[1], val[2], val[3]);
        }
        else if constexpr (std::is_same<T, glm::mat4>::value) {
          glUniformMatrix4fv(location, 1, false, &val[0][0]);
        }
        else {
          // the '&& sizeof(T)' is there to stop the compiler from complaining about the assertion
          static_assert(false && sizeof(T), "Unsupported uniform type");
        }
      }

      unsigned int get_uniform_location(const std::string& name) const;

      void bind() const;
      void unbind() const;

    private:
      // mvp uniforms
      unsigned int model_uniform;
      unsigned int view_uniform;
      unsigned int proj_uniform;

      // lighting uniforms
      unsigned int ambient_uniform;
      unsigned int diffuse_uniform;
      unsigned int specular_uniform;
      unsigned int shininess_uniform;

      // texture uniform
      unsigned int texture_uniform;

      // shader ids
      unsigned int vshader_id;
      unsigned int fshader_id;
      unsigned int prog_id;
  };
}
