#pragma once

#include "scenenode.hpp"

namespace laika3d {
  class SceneGraph {
    public:
      SceneGraph();
      ~SceneGraph();

    private:
      std::shared_ptr<SceneNode> root;
  };
}
