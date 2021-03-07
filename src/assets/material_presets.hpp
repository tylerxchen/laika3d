#pragma once

#include "material.hpp"

namespace laika3d {
  const Material GOLD = {
    glm::vec3(0.24725, 0.1995, 0.0745),
    glm::vec3(0.75164, 0.60648, 0.22648),
    glm::vec3(0.62828, 0.5558, 0.36607),
    51.2f
  };

  const Material JADE = {
    glm::vec3(0.135, 0.2225, 0.1575),
    glm::vec3(0.54, 0.89, 0.63),
    glm::vec3(0.3162, 0.3162, 0.3162),
    12.8f
  };
}
