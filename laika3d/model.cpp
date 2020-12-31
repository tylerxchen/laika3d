#include "model.hpp"

#include <fstream>
#include <stdexcept>
#include <sstream>
#include <optional>
#include <iostream>

using namespace laika3d;

Model::Model(const std::string& file_path)
  : translation(1.0f), rotation(1.0f), scaling(1.0f), model(1.0f) {
  // obj file parsing
  std::ifstream file;
  file.open(file_path);

  std::string line;

  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;

  while (std::getline(file, line)) {
    std::istringstream ss(line);
    std::string start;
    ss >> start;

    if (start == "v") {
      // vertex
      float v1, v2, v3;
      ss >> v1;
      ss >> v2;
      ss >> v3;
      vertices.push_back({v1, v2, v3});
    }
    else if (start == "vn") {
      // vertex normal
      // unhandled right now
    }
    else if (start == "vt") {
      // texture mapping
      // unhandled right now
    }
    else if (start == "f") {
      std::vector<unsigned int> polygon;
      std::string element;
      while (ss >> element) {
        std::size_t slash_pos = element.find('/');
        unsigned long index;
        if (slash_pos != std::string::npos) {
          index = std::stoul(element.substr(0, slash_pos)) - 1;
        }
        else {
          index = std::stoul(element) - 1;
        }

        polygon.push_back(index);
      }

      if (polygon.size() < 3) {
        throw std::runtime_error("Too few vertex indices to form polygon");
      }

      unsigned int origin = polygon[0];
      unsigned int other = 2;

      while (other < polygon.size()) {
        indices.push_back(origin);
        indices.push_back(polygon[other - 1]);
        indices.push_back(polygon[other]);
        other++;
      }
    }
    else if (start == "o") {
      // object name
      // unhandled right now
    }
    else if (start == "g") {
      // group name
      // unhandled right now
    }
    else if (!(start == "#" || start == "")) {
      // if it's not a comment, then it's invalid
      throw std::runtime_error("Unknown beginning of line '" + start + "'");
    }
  }

  if (indices.size() % 3 != 0) {
    throw std::runtime_error("Index buffer size must be a multiple of 3");
  }

  for (const auto& i : indices) {
    if (i >= vertices.size()) {
      throw std::runtime_error("Face references an out of bounds vertex");
    }
  }

  vbuf = std::make_unique<VertexBuffer>(vertices);
  ibuf = std::make_unique<IndexBuffer>(indices);
}

Model::Model(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
  : vbuf(std::make_unique<VertexBuffer>(vertices)), ibuf(std::make_unique<IndexBuffer>(indices)),
    translation(1.0f), rotation(1.0f), scaling(1.0f), model(1.0f) {}

void Model::calc_model_mat() {
  model = translation * rotation * scaling;
}

void Model::set_translation(float x, float y, float z) {
  translation = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
  calc_model_mat();
}

void Model::set_rotation_x(float angle) {
  rotation = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(1.0f, 0.0f, 0.0f));
  calc_model_mat();
}

void Model::set_rotation_y(float angle) {
  rotation = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f));
  calc_model_mat();
}

void Model::set_rotation_z(float angle) {
  rotation = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f));
  calc_model_mat();
}

void Model::set_scale(float x, float y, float z) {
  scaling = glm::scale(glm::mat4(1.0f), glm::vec3(x, y, z));
  calc_model_mat();
}

void Model::bind() const {
  vbuf->bind();
  ibuf->bind();
}

void Model::unbind() const {
  vbuf->unbind();
  ibuf->unbind();
}
