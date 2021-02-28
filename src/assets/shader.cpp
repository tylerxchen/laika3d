#include "shader.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <vector>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace laika3d;

Shader::Shader(const std::string& path) {
  vshader_id = glCreateShader(GL_VERTEX_SHADER);
  fshader_id = glCreateShader(GL_FRAGMENT_SHADER);

  enum class ShaderType {
    NONE,
    VERTEX,
    FRAGMENT,
  } shader_type = ShaderType::NONE;

  std::string vertex_source;
  std::string fragment_source;
  std::ifstream file(path, std::ios::in);
  if (file.is_open()) {
    std::stringstream vertex_stream;
    std::stringstream fragment_stream;
    std::string line;
    while (std::getline(file, line)) {
      if (line == "#VERTEX") {
        shader_type = ShaderType::VERTEX;
      }
      else if (line == "#FRAGMENT") {
        shader_type = ShaderType::FRAGMENT;
      }
      else {
        switch (shader_type) {
          case ShaderType::VERTEX:
            vertex_stream << line << '\n';
            break;
          case ShaderType::FRAGMENT:
            fragment_stream << line << '\n';
            break;
          case ShaderType::NONE:
            break;
        }
      }
    }

    vertex_source = vertex_stream.str();
    fragment_source = fragment_stream.str();

    file.close();
  }
  else {
    throw std::runtime_error("Unable to load shader file");
  }

  //std::cout << "Vertex Shader:" << std::endl << vertex_source << std::endl;
  //std::cout << "Fragment Shader:" << std::endl << fragment_source << std::endl;

  auto result = GL_FALSE;
  int log_len;

  auto vertex_source_raw = vertex_source.c_str();
  glShaderSource(vshader_id, 1, &vertex_source_raw, nullptr);
  glCompileShader(vshader_id);

  glGetShaderiv(vshader_id, GL_COMPILE_STATUS, &result);
  glGetShaderiv(vshader_id, GL_INFO_LOG_LENGTH, &log_len);
  if (log_len > 0) {
    std::vector<char> error_msg(log_len + 1);
    glGetShaderInfoLog(vshader_id, log_len, nullptr, error_msg.data());
    throw std::runtime_error(error_msg.data());
  }

  auto fragment_source_raw = fragment_source.c_str();
  glShaderSource(fshader_id, 1, &fragment_source_raw, nullptr);
  glCompileShader(fshader_id);
  
  glGetShaderiv(fshader_id, GL_COMPILE_STATUS, &result);
  glGetShaderiv(fshader_id, GL_INFO_LOG_LENGTH, &log_len);
  if (log_len > 0) {
    std::vector<char> error_msg(log_len + 1);
    glGetShaderInfoLog(fshader_id, log_len, nullptr, error_msg.data());
    throw std::runtime_error(error_msg.data());
  }

  prog_id = glCreateProgram();
  glAttachShader(prog_id, vshader_id);
  glAttachShader(prog_id, fshader_id);
  glLinkProgram(prog_id);

  glDetachShader(prog_id, vshader_id);
  glDetachShader(prog_id, fshader_id);
  glDeleteShader(vshader_id);
  glDeleteShader(fshader_id);

  model_uniform = glGetUniformLocation(prog_id, "model");
  if (model_uniform == -1) {
    throw std::runtime_error("Shaders must have a mat4 uniform called 'model'");
  }

  view_uniform = glGetUniformLocation(prog_id, "view");
  if (view_uniform == -1) {
    throw std::runtime_error("Shaders must have a mat4 uniform called 'view'");
  }

  proj_uniform = glGetUniformLocation(prog_id, "proj");
  if (proj_uniform == -1) {
    throw std::runtime_error("Shaders must have a mat4 uniform called 'proj'");
  }

  texture_uniform = glGetUniformLocation(prog_id, "texture_sampler");
  if (texture_uniform == -1) {
    throw std::runtime_error("Shaders must have a sampler2D uniform called 'texture_sampler'");
  }
}

Shader::~Shader() {
  glDeleteProgram(prog_id);
}

template<typename T>
void Shader::set_uniform(unsigned int location, const T& val) const {
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

unsigned int Shader::get_uniform_location(const std::string& name) const {
  return glGetUniformLocation(prog_id, name.c_str());
}

unsigned int Shader::get_prog_id() const {
  return prog_id;
}

unsigned int Shader::get_model_mat_id() const {
  return model_uniform;
}

unsigned int Shader::get_view_mat_id() const {
  return view_uniform;
}
unsigned int Shader::get_proj_mat_id() const {
  return proj_uniform;
}

unsigned int Shader::get_texture_id() const {
  return texture_uniform;
}

void Shader::bind() const {
  glUseProgram(prog_id);
}

void Shader::unbind() const {
  glUseProgram(0);
}
