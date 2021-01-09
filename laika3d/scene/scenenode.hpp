#pragma once

#include <vector>
#include <memory>

namespace laika3d {
  class SceneNode {
    public:
      SceneNode();
      virtual ~SceneNode();
      void add_child(std::shared_ptr<SceneNode> child) { children.push_back(child); }

      std::vector<std::shared_ptr<SceneNode>>::const_iterator children_begin() const { return children.begin(); }
      std::vector<std::shared_ptr<SceneNode>>::const_iterator children_end() const { return children.end(); }

    protected:
      std::vector<std::shared_ptr<SceneNode>> children;
  };
}
