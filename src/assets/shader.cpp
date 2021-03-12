#include "shader.hpp"

#include <vector>
#include <stdexcept>
#include <fstream>
#include <sstream>

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

  ambient_uniform = glGetUniformLocation(prog_id, "material.ambient");
  //if (ambient_uniform == -1) {
  //  throw std::runtime_error("Shaders must have a struct called 'material' with a vec3 member called 'ambient'");
  //}

  diffuse_uniform = glGetUniformLocation(prog_id, "material.diffuse");
  //if (diffuse_uniform == -1) {
  //  throw std::runtime_error("Shaders must have a struct called 'material' with a vec3 member called 'diffuse'");
  //}

  specular_uniform = glGetUniformLocation(prog_id, "material.specular");
  //if (specular_uniform == -1) {
  //  throw std::runtime_error("Shaders must have a struct called 'material' with a vec3 member called 'specular'");
  //}

  shininess_uniform = glGetUniformLocation(prog_id, "material.shininess");
  //if (shininess_uniform == -1) {
  //  throw std::runtime_error("Shaders must have a struct called 'material' with a float member called 'shininess'");
  //}
}

Shader::~Shader() {
  glDeleteProgram(prog_id);
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

unsigned int Shader::get_ambient_id() const {
  return ambient_uniform;
}

unsigned int Shader::get_diffuse_id() const {
  return diffuse_uniform;
}

unsigned int Shader::get_specular_id() const {
  return specular_uniform;
}

unsigned int Shader::get_shininess_id() const {
  return shininess_uniform;
}

void Shader::bind() const {
  glUseProgram(prog_id);
}

void Shader::unbind() const {
  glUseProgram(0);
}
