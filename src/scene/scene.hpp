#pragma once

#include "scenenode.hpp"

#include <map>

namespace laika3d {
  class Scene {
    public:
      Scene();
      ~Scene();

      void add_node(const std::string& parent_name, std::shared_ptr<SceneNode> child);
      void delete_subtree(const std::string& name);
      std::shared_ptr<SceneNode> find_node(const std::string& name);

    private:
      std::shared_ptr<SceneNode> root;
  };
}
