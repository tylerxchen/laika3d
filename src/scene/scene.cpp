#include "scene.hpp"
#include "transformationnode.hpp"

#include <stack>

using namespace laika3d;

Scene::Scene()
: root(std::static_pointer_cast<SceneNode>(std::make_shared<TransformationNode>("root"))) {}

Scene::~Scene() {}

void Scene::add_node(const std::string& parent_name, std::shared_ptr<SceneNode> child) {
  auto parent = find_node(parent_name);

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

std::shared_ptr<SceneNode> Scene::find_node(const std::string& name) {
  std::stack<std::shared_ptr<SceneNode>> s;
  s.push(root);
  while (!s.empty()) {
    auto node = s.top();
    s.pop();

    if (node->get_name() == name) {
      return node;
    }

    for (auto it = node->children_begin(); it != node->children_end(); ++it) {
      s.push(*it);
    }
  }

  return nullptr;
}
