#include "texture.hpp"

#include "vendor/lodepng.h"

#include <stdexcept>

using namespace laika3d;

Texture::Texture(const std::string& path) {
  if (lodepng::decode(image, width, height, path.c_str()) != 0) {
    throw std::runtime_error("Unable to load texture from '" + path + "'");
  }
}
