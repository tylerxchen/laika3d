#include "texture.hpp"

#include "../vendor/lodepng.h"
#include <GL/glew.h>

#include <stdexcept>

using namespace laika3d;

Texture::Texture(const std::string& path) {
  if (lodepng::decode(image, width, height, path.c_str()) != 0) {
    throw std::runtime_error("Unable to load texture from '" + path + "'");
  }

  glGenTextures(1, &renderer_id);
  glBindTexture(GL_TEXTURE_2D, renderer_id);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, image.data());

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

Texture::~Texture() {
  glDeleteTextures(1, &renderer_id);
}

void Texture::bind() const {
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, renderer_id);
}

void Texture::unbind() const {
  glBindTexture(GL_TEXTURE_2D, 0);
}
