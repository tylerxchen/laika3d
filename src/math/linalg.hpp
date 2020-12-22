#pragma once

#include <array>
#include "vec3.hpp"
#include <cmath>

namespace tc3d {
  namespace math {
    template<std::size_t R, std::size_t C>
    class Matrix {
      public:
        Matrix<R, C>() : mat{} {}
        Matrix<R, C>(const std::array<std::array<double, C>, R>& a) : mat(a) {}

        std::array<double, C>& operator[](std::size_t i) { return mat[i]; }
        const std::array<double, C>& operator[](std::size_t i) const { return mat[i]; }

        template<std::size_t N>
        Matrix<R, N> operator*(const Matrix<C, N>& other) const {
          Matrix<R, N> rv;
          for (std::size_t i = 0; i < R; ++i) {
            for (std::size_t j = 0; j < N; ++j) {
              for (std::size_t k = 0; k < C; ++k) {
                rv[i][j] += mat[i][k] * other[k][j];
              }
            }
          }
          return rv;
        }

        Matrix<R, C> operator*(double rhs) const {
          Matrix<R, C> rv = *this;
          for (std::size_t i = 0; i < R; ++i) {
            for (std::size_t j = 0; j < C; ++j) {
              rv[i][j] *= rhs;
            }
          }
          return rv;
        }

        Matrix<R, C> operator+(const Matrix<R, C>& other) {
          Matrix<R, C> rv = *this;
          for (std::size_t i = 0; i < R; ++i) {
            for (std::size_t j = 0; j < C; ++j) {
              rv[i][j] += other[i][j];
            }
          }
          return rv;
        }

        Matrix<R, C> operator-(const Matrix<R, C>& other) {
          Matrix<R, C> rv = *this;
          for (std::size_t i = 0; i < R; ++i) {
            for (std::size_t j = 0; j < C; ++j) {
              rv[i][j] -= other[i][j];
            }
          }
          return rv;
        }

        std::size_t size() const { return R * C; }
        std::size_t rows() const { return R; }
        std::size_t cols() const { return C; }

      private:
        std::array<std::array<double, C>, R> mat;
    };

    inline Vec3 rotate_x(const Vec3& v, double theta) {
      auto rotation = Matrix<3, 3>({{
        {1, 0, 0},
        {0, cos(theta), -sin(theta)},
        {0, sin(theta), cos(theta)},
      }});
      auto v_as_col = Matrix<3, 1>({{
        {v[0]},
        {v[1]},
        {v[2]},
      }});

      auto result = rotation * v_as_col;
      return Vec3(result[0][0], result[1][0], result[2][0]);
    }
  }
}
