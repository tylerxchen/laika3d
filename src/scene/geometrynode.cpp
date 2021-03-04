#include "geometrynode.hpp"
#include <GL/glew.h>
#include <iostream>

using namespace laika3d;

GeometryNode::GeometryNode(const std::string& n)
  : SceneNode(n) {}

GeometryNode::~GeometryNode() {}

void GeometryNode::bind() const {
  if (mesh) { mesh->bind(); }
  if (texture) { texture->bind(); }
  if (shader) { shader->bind(); }
}

void GeometryNode::unbind() const {
  if (mesh) { mesh->unbind(); }
  if (texture) { texture->unbind(); }
  if (shader) { shader->unbind(); }
}

void GeometryNode::set_mvp(const glm::mat4& model, const glm::mat4& view, const glm::mat4& proj) {
  shader->set_uniform(shader->get_model_mat_id(), model);
  shader->set_uniform(shader->get_view_mat_id(), view);
  shader->set_uniform(shader->get_proj_mat_id(), proj);
}
