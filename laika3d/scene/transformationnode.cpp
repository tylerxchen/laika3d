#include "transformationnode.hpp"

using namespace laika3d;

TransformationNode::TransformationNode(const std::string& n)
  : translation(0.0f, 0.0f, 0.0f),
    scale(1.0f, 1.0f, 1.0f),
    rotation(1.0f, 0.0f, 0.0f, 0.0f),
    SceneNode(n) {}

TransformationNode::~TransformationNode() {}

glm::mat4 TransformationNode::get_model_matrix() const {
  auto t = glm::translate(glm::mat4(1.0f), translation);
  auto r = glm::toMat4(rotation);
  auto s = glm::scale(glm::mat4(1.0f), scale);
  return t * r * s;
}

void TransformationNode::set_scale(glm::vec3 s) {
  scale = s;
}

void TransformationNode::set_translation(glm::vec3 t) {
  translation = t;
}

void TransformationNode::rotate_x(float angle) {
  rotation = glm::rotate(rotation, angle, glm::vec3(1.0f, 0.0f, 0.0f));
}

void TransformationNode::rotate_y(float angle) {
  rotation = glm::rotate(rotation, angle, glm::vec3(0.0f, 1.0f, 0.0f));
}

void TransformationNode::rotate_z(float angle) {
  rotation = glm::rotate(rotation, angle, glm::vec3(0.0f, 0.0f, 1.0f));
}

void TransformationNode::reset_rotation() {
  rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
}
