#pragma once

#include <array>
#include <cmath>

namespace tc3d {
  namespace math {
    class Vec3 {
      public:
        Vec3() : e{0, 0, 0} {}
        Vec3(double x, double y, double z) : e{x, y, z} {}

        double x() const { return e[0]; }
        double y() const { return e[1]; }
        double z() const { return e[2]; }

        double& x() { return e[0]; }
        double& y() { return e[1]; }
        double& z() { return e[2]; }


        double& operator[](std::size_t i) { return e[i]; }
        const double& operator[](std::size_t i) const { return e[i]; }
        Vec3 operator+(const Vec3& other) { return Vec3(e[0] + other[0], e[1] + other[1], e[2] + other[2]); }

        double length() const { return sqrt(length_squared()); };
        double length_squared() const { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; }

        Vec3 normalized() const {
          double len = length();
          return Vec3(e[0] / len, e[1] / len, e[2] / len);
        }

      private:
        std::array<double, 3> e;
    };

    inline double dot(const Vec3& u, const Vec3& v) {
      return u[0] * v[0] + u[1] * v[1] + u[2] * v[2];
    }

    inline Vec3 cross(Vec3 u, Vec3 v) {
      return Vec3(
        u[1] * v[2] - u[2] * v[1],
        u[2] * v[0] - u[0] * v[2],
        u[0] * v[1] - u[1] * v[0]
      );
    }
  }
}
