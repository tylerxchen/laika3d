#include "shaderutils.hpp"

#include <fstream>
#include <sstream>

using namespace tc3d::rendering;

void load_shaders(const std::string& vertex_path, const std::string& fragment_path) {
  auto vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
  auto fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

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
  
}
