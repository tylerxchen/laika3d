#include "scenegraph.hpp"

#include <glm/gtc/matrix_transform.hpp>

using namespace laika3d;

SceneNode::SceneNode(const std::string& n)
  : name(n), translation(1.0f), rotation(1.0f), scaling(1.0f), model(1.0f) {}

SceneNode::~SceneNode() {
  // do nothing
}

void SceneNode::calc_model_mat() {
  model = translation * rotation * scaling;
}

void SceneNode::set_translation(float x, float y, float z) {
  translation = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
  calc_model_mat();
}

void SceneNode::set_rotation_x(float angle) {
  rotation = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(1.0f, 0.0f, 0.0f));
  calc_model_mat();
}

void SceneNode::set_rotation_y(float angle) {
  rotation = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f));
  calc_model_mat();
}

void SceneNode::set_rotation_z(float angle) {
  rotation = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f));
  calc_model_mat();
}

void SceneNode::set_scale(float x, float y, float z) {
  scaling = glm::scale(glm::mat4(1.0f), glm::vec3(x, y, z));
  calc_model_mat();
}
