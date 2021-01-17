#include "scene.hpp"
#include "transformationnode.hpp"

#include <stack>

using namespace laika3d;

Scene::Scene()
: root(std::static_pointer_cast<SceneNode>(std::make_shared<TransformationNode>("root"))) {}

Scene::~Scene() {}

void Scene::add_node(const std::string& parent_name, std::shared_ptr<SceneNode> child) {
  std::stack<std::shared_ptr<SceneNode>> s;
  std::shared_ptr<SceneNode> parent;
  s.push(root);
  while (!s.empty()) {
    auto node = s.top();
    s.pop();

    if (parent->get_name() == parent_name) {
      parent = node;
      break;
    }

    for (auto it = node->children_begin(); it != node->children_end(); ++it) {
      s.push(*it);
    }
  }

  if (parent) {
    parent->add_child(child);
  }
}

void Scene::delete_subtree(const std::string& name) {
  std::stack<std::shared_ptr<SceneNode>> s;
  s.push(root);
  while (!s.empty()) {
    auto node = s.top();
    s.pop();

    for (auto it = node->children_begin(); it != node->children_end(); ++it) {
      if ((*it)->get_name() == name) {
        node->erase_child(it);
        return;
      }
    }
  }
}
