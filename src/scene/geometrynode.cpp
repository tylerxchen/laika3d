#include "geometrynode.hpp"
#include <GL/glew.h>

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

void GeometryNode::set_mvp(const glm::mat4& mvp) {
  glUniformMatrix4fv(shader->get_mvp_id(), 1, GL_FALSE, &mvp[0][0]);
}
