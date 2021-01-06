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

Shader::Shader(const std::string& vertex_path, const std::string& fragment_path) {
  vshader_id = glCreateShader(GL_VERTEX_SHADER);
  fshader_id = glCreateShader(GL_FRAGMENT_SHADER);

  std::string vertex_source;
  std::ifstream vertex_stream(vertex_path, std::ios::in);
  if (vertex_stream.is_open()) {
    std::stringstream ss;
    ss << vertex_stream.rdbuf();
    vertex_source = ss.str();
    vertex_stream.close();
  }
  else {
    throw std::runtime_error("Unable to load vertex shader file");
  }

  std::string fragment_source;
  std::ifstream fragment_stream(fragment_path, std::ios::in);
  if (fragment_stream.is_open()) {
    std::stringstream ss;
    ss << fragment_stream.rdbuf();
    fragment_source = ss.str();
    fragment_stream.close();
  }
  else {
    throw std::runtime_error("Unable to load fragment shader file");
  }

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

  mvp_uniform = glGetUniformLocation(prog_id, "mvp");
  if (mvp_uniform == -1) {
    throw std::runtime_error("Shaders must have a mat4 uniform called 'MVP'");
  }
}

template<typename T>
void Shader::uniform(unsigned int location, const T& val) const {
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

void Shader::bind() const {
  glUseProgram(prog_id);
}

void Shader::unbind() const {
  glUseProgram(0);
}

Shader::~Shader() {
  glDeleteProgram(prog_id);
}
