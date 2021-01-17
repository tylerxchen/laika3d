#pragma once

#include <glm/glm.hpp>

#include "resource.hpp"
#include "texture.hpp"
#include "mesh.hpp"
#include "shader.hpp"

#include <optional>
#include <memory>
#include <map>
#include <any>

namespace laika3d {
  class ResourceManager {
    public:
      ResourceManager();
      ~ResourceManager();

      template<typename T>
      std::optional<std::shared_ptr<T>> load(const std::string& path);

    private:
      void cleanup();

      std::map<std::string, std::shared_ptr<Resource>> resources;
  };
}
