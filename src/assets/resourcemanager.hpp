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
      std::optional<std::shared_ptr<T>> load(const std::string& path) {
        std::shared_ptr<T> res;

        if (resources.find(path) != resources.end()) {
          res = std::dynamic_pointer_cast<T>(resources[path]);
          
          // res will be a null pointer if the path does not refer to the resource type requested
          if (!res) {
            return {};
          }

          cleanup();
        }
        else {
          cleanup();
          try {
            res = std::make_shared<T>(path);
          }
          catch (std::exception e) {
            return {};
          }

          resources[path] = std::static_pointer_cast<Resource>(res);
        }

        return res;
      }

      std::size_t get_resource_count() { return resources.size(); }

    private:
      void cleanup();

      std::map<std::string, std::shared_ptr<Resource>> resources;
  };
}
