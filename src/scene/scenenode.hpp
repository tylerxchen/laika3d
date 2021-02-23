#pragma once

#include <vector>
#include <memory>
#include <string>

namespace laika3d {
  class SceneNode {
    public:
      SceneNode(const std::string& n) : name(n) {}
      virtual ~SceneNode() {}

      void add_child(std::shared_ptr<SceneNode> child) { children.push_back(child); }
      void erase_child(std::vector<std::shared_ptr<SceneNode>>::const_iterator it) { children.erase(it); }

      std::vector<std::shared_ptr<SceneNode>>::const_iterator children_begin() const { return children.begin(); }
      std::vector<std::shared_ptr<SceneNode>>::const_iterator children_end() const { return children.end(); }

      std::string get_name() { return name; }
      std::size_t get_child_count() { return children.size(); }

    protected:
      std::string name;
      std::vector<std::shared_ptr<SceneNode>> children;
  };
}
