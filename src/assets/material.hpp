#pragma once

#include <glm/glm.hpp>

namespace laika3d {
  struct Material {
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
  };
}
