#include "mesh.hpp"

#include <fstream>
#include <sstream>
#include <unordered_map>

using namespace laika3d;

Mesh::Mesh(const std::string& file_path) {
  // obj file parsing
  std::ifstream file(file_path, std::ios::in);

  struct Attribute {
    float x;
    float y;
    float z;
  };

  std::vector<Attribute> vert_vals;
  std::vector<Attribute> tex_vals;
  std::vector<Attribute> norm_vals;

  std::vector<unsigned int> vertex_indices;
  std::vector<unsigned int> texture_indices;
  std::vector<unsigned int> normal_indices;

  if (file.is_open()) {
    std::string line;
    while (std::getline(file, line)) {
      std::istringstream ss(line);
      std::string start;
      ss >> start;

      if (start == "v") {
        float v1, v2, v3;
        ss >> v1; ss >> v2; ss >> v3;

        vert_vals.push_back({ v1, v2, v3 });
      }
      else if (start == "vn") {
        float n1, n2, n3;
        ss >> n1; ss >> n2; ss >> n3;
        
        norm_vals.push_back({ n1, n2, n3 });
      }
      else if (start == "vt") {
        float t1, t2, t3;
        ss >> t1; ss >> t3; ss >> t3;

        tex_vals.push_back({ t1, t2, t3 });
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
  }
  else {
    throw std::runtime_error("Unable to load model file");
  }

  file.close();

  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;
  std::unordered_map<unsigned long long, unsigned int> vert_map;
  
  typedef unsigned long long ull;
  
  for (int i = 0; i < vertex_indices.size(); ++i) {
    unsigned long long key = (ull(normal_indices[i] & 0xFFFF) << 32) | ((texture_indices[i] & 0xFFFF) << 16) | (vertex_indices[i] & 0xFFFF);
    unsigned int index;
    auto search = vert_map.find(key);

    if (search != vert_map.end()) {
      index = search->second;
    }
    else {
      Attribute vert;
      if (vertex_indices[i] < vert_vals.size())
        vert = vert_vals[vertex_indices[i]];

      Attribute norm;
      if (normal_indices[i] < norm_vals.size())
        norm = norm_vals[normal_indices[i]];
      
      Attribute tex;
      if (texture_indices[i] < tex_vals.size())
        tex = tex_vals[texture_indices[i]];
      
      vertices.push_back({
        vert.x, vert.y, vert.z,
        norm.x, norm.y, norm.z,
        tex.x, tex.y, tex.z
      });

      index = vertices.size() - 1;
      vert_map[key] = index;
    }

    indices.push_back(index);
  }

  vbuf = std::make_unique<VertexBuffer>(vertices);
  v_indices = std::make_unique<IndexBuffer>(indices);
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
