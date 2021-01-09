#include "mesh.hpp"

#include <fstream>
#include <sstream>

using namespace laika3d;

Mesh::Mesh(const std::string& file_path) {
    // obj file parsing
  std::ifstream file;
  file.open(file_path);

  std::string line;

  std::vector<Vertex> vertices;
  std::vector<unsigned int> vertex_indices;
  std::vector<unsigned int> texture_indices;
  std::vector<unsigned int> normal_indices;

  unsigned int vertex_count = 0;
  unsigned int normal_count = 0;
  unsigned int texture_count = 0;

  while (std::getline(file, line)) {
    std::istringstream ss(line);
    std::string start;
    ss >> start;

    if (start == "v") {
      // vertex
      if (vertex_count >= vertices.size()) {
        vertices.resize(vertex_count + 1);
      }

      float v1, v2, v3;
      ss >> v1; ss >> v2; ss >> v3;

      vertices[vertex_count].x = v1;
      vertices[vertex_count].y = v2;
      vertices[vertex_count].z = v3;
      ++vertex_count;
    }
    else if (start == "vn") {
      // vertex normal
      if (normal_count >= vertices.size()) {
        vertices.resize(normal_count + 1);
      }

      float n1, n2, n3;
      ss >> n1; ss >> n2; ss >> n3;

      vertices[normal_count].norm_x = n1;
      vertices[normal_count].norm_y = n2;
      vertices[normal_count].norm_z = n3;
      ++normal_count;
    }
    else if (start == "vt") {
      // texture mapping
      if (texture_count >= vertices.size()) {
        vertices.resize(texture_count + 1);
      }

      float t1, t2, t3;
      ss >> t1; ss >> t3; ss >> t3;

      vertices[texture_count].tex_x = t1;
      vertices[texture_count].tex_y = t2;
      vertices[texture_count].tex_z = t3;
      ++texture_count;
    }
    else if (start == "f") {
      struct VertexIndices {
        unsigned int v;
        unsigned int vt;
        unsigned int vn;
      };

      std::vector<VertexIndices> polygon;
      std::string element;
      while (ss >> element) {
        VertexIndices v;
        // this isn't particularly fast but it's simple and robust
        if (std::sscanf(element.c_str(), "%d/%d/%d", &v.v, &v.vt, &v.vn) == 3) {
          --v.v;
          --v.vt;
          --v.vn;
        }
        else if (std::sscanf(element.c_str(), "%d//%d", &v.v, &v.vn) == 2) {
          --v.v;
          v.vt = 0;
          --v.vn;
        }
        else if (std::sscanf(element.c_str(), "%d/%d", &v.v, &v.vt) == 2) {
          v.vn = 0;
        }
        else if (std::sscanf(element.c_str(), "%d", &v.v) == 1) {
          --v.v;
          v.vt = 0;
          v.vn = 0;
        }
        else {
          throw std::runtime_error("Invalid face format");
        }

        polygon.push_back(v);
      }

      if (polygon.size() < 3) {
        throw std::runtime_error("Too few vertex indices to form polygon");
      }

      unsigned int origin = 0;
      unsigned int other = 2;

      while (other < polygon.size()) {
        vertex_indices.push_back(polygon[origin].v);
        texture_indices.push_back(polygon[origin].vt);
        normal_indices.push_back(polygon[origin].vn);

        vertex_indices.push_back(polygon[other - 1].v);
        texture_indices.push_back(polygon[other - 1].vt);
        normal_indices.push_back(polygon[other - 1].vn);

        vertex_indices.push_back(polygon[other].v);
        texture_indices.push_back(polygon[other].vt);
        normal_indices.push_back(polygon[other].vn);

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
    else if (!(start == "" || start[0] == '#')) {
      // if it's not a comment, then it's invalid
      throw std::runtime_error("Unknown beginning of line '" + start + "'");
    }
  }

  if (vertex_indices.size() % 3 != 0) {
    throw std::runtime_error("Index buffer size must be a multiple of 3");
  }

  for (const auto& i : vertex_indices) {
    if (i >= vertices.size()) {
      throw std::runtime_error("Face references an out of bounds vertex");
    }
  }

  vbuf = std::make_unique<VertexBuffer>(vertices);
  v_indices = std::make_unique<IndexBuffer>(vertex_indices);
  vt_indices = std::make_unique<IndexBuffer>(texture_indices);
  vn_indices = std::make_unique<IndexBuffer>(normal_indices);
}

Mesh::~Mesh() {}

void Mesh::bind() const {
  vbuf->bind();
  v_indices->bind();
}

void Mesh::unbind() const {
  vbuf->unbind();
  v_indices->unbind();
}
