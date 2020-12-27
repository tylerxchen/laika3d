#pragma once

#include "../math/matrix.hpp"

namespace tc3d {
  namespace rendering {
    class Camera {
      public:
        Camera();
        ~Camera();

        void set_position(double x, double y, double z);
        void set_direction(double x, double y, double z);
      private:
        math::Vec3 position;
        math::Vec3 direction;
    };
  }
}
