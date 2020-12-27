#include "shader.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <stdexcept>
#include <fstream>
#include <sstream>

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
