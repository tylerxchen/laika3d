#pragma once

#include <string>
#include <vector>

namespace laika3d {
  class Texture {
    public:
      Texture(const std::string& path);
      ~Texture();
    
    private:
      std::vector<unsigned char> image;
      unsigned int width;
      unsigned int height;
  };
}
