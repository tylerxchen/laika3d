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
  glUniformMatrix4fv(shader->get_model_mat_id(), 1, GL_FALSE, &model[0][0]);
  glUniformMatrix4fv(shader->get_view_mat_id(), 1, GL_FALSE, &view[0][0]);
  glUniformMatrix4fv(shader->get_proj_mat_id(), 1, GL_FALSE, &proj[0][0]);
}
