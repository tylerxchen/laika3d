#pragma once

#include <glm/glm.hpp>

#include "texture.hpp"
#include "mesh.hpp"
#include "shader.hpp"

#include <optional>
#include <memory>
#include <map>

namespace laika3d {
  class ResourceManager {
    public:
      static ResourceManager& get() {
        static ResourceManager singleton;
        return singleton;
      }

      ~ResourceManager();

      std::optional<std::shared_ptr<Texture>> load_texture(const std::string& path);
      std::optional<std::shared_ptr<Mesh>> load_mesh(const std::string& path);
      std::optional<std::shared_ptr<Shader>> load_shader(const std::string& path);
    
    private:
      ResourceManager();
  };
}