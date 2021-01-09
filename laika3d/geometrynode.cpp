#include "geometrynode.hpp"

using namespace laika3d;

GeometryNode::GeometryNode() { }

GeometryNode::~GeometryNode() { }

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
