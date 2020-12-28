#include "model.hpp"

#include <fstream>
#include <stdexcept>
#include <sstream>

using namespace laika3d;

Model::Model(const std::string& file_path) {
  // obj file parsing
  std::ifstream file;
  file.exceptions(std::fstream::failbit | std::fstream::badbit);
  file.open(file_path);

  while (!file.eof()) {
    std::string line;
    std::getline(file, line);

    std::istringstream ss(line);

    if (line.substr(0, 2) == "v ") {
      // vertex
      float v1, v2, v3;
      ss >> v1;
      ss >> v2;
      ss >> v3;
      vbuf.append({v1, v2, v3});

    }
    else if (line.substr(0, 2) == "vn") {
      // vertex normal
      // unhandled right now
    }
    else if (line.substr(0, 2) == "vt") {
      // texture mapping
      // unhandled right now
    }
    else if (line.substr(0, 2) == "f ") {
      // defines a face
      unsigned int f1, f2, f3;
      ss >> f1;
      ss >> f2;
      ss >> f3;
      ibuf.append(f1);
      ibuf.append(f2);
      ibuf.append(f3);
    }
    else if (line.substr(0, 2) != "# ") {
      // if it's not a comment, then it's invalid
      throw std::runtime_error("Unknown beginning of line");
    }
  }
}

Model::Model(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
  : vbuf(vertices), ibuf(indices) {
  init_mats();
}

void Model::init_mats() {
  translation = glm::translate(glm::mat4(), glm::vec3());
  rotation = glm::rotate(glm::mat4(), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
  scaling = glm::scale(glm::mat4(), glm::vec3(1.0f, 1.0f, 1.0f));
  calc_model_mat();
}

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

void Model::unbind() {
  vbuf.unbind();
  ibuf.unbind();
}
