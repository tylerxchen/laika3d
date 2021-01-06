#pragma once

#include <string>
#include <vector>

namespace laika3d {
  class Texture {
    public:
      Texture(const std::string& path);
      ~Texture();

      void bind() const;
      void unbind() const;
    private:
      std::vector<unsigned char> image;
      unsigned int width;
      unsigned int height;

      unsigned int renderer_id;
  };
}
