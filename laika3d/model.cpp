#include "model.hpp"

using namespace laika3d;

Model::Model(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
  : vbuf(vertices), ibuf(indices) {}

void Model::calc_model_mat() {
  model = translation * rotation * scaling;
}

void Model::translate(float x, float y, float z) {
  translation = glm::translate(glm::mat4(), glm::vec3(x, y, z));
  calc_model_mat();
}

void Model::rotate_x(float angle) {
  rotation = glm::rotate(glm::mat4(), angle, glm::vec3(1.0f, 0.0f, 0.0f));
  calc_model_mat();
}

void Model::rotate_y(float angle) {
  rotation = glm::rotate(glm::mat4(), angle, glm::vec3(0.0f, 1.0f, 0.0f));
  calc_model_mat();
}

void Model::rotate_z(float angle) {
  rotation = glm::rotate(glm::mat4(), angle, glm::vec3(0.0f, 1.0f, 0.0f));
  calc_model_mat();
}

void Model::scale(float x, float y, float z) {
  scaling = glm::scale(glm::mat4(), glm::vec3(x, y, z));
  calc_model_mat();
}

glm::mat4 Model::mat() {
  return model;
}

void Model::bind() {
  vbuf.bind();
  ibuf.bind();
}
