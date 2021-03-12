#pragma once

#include <glm/glm.hpp>

#include "scenenode.hpp"
#include "geometrynode.hpp"
#include "camera.hpp"

#include <map>
#include <queue>

namespace laika3d {
  struct Scene {
      Scene();
      ~Scene();

      std::shared_ptr<SceneNode> root;
      std::shared_ptr<GeometryNode> skybox;
      
      Camera cam;

      void add_node(const std::string& parent_name, std::shared_ptr<SceneNode> child);
      void delete_subtree(const std::string& name);
      std::shared_ptr<SceneNode> find_node(const std::string& name);
  };
}
