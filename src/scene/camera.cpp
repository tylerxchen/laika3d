#include "camera.hpp"

using namespace laika3d;

Camera::Camera()
  : projection(glm::perspective(glm::radians(45.0f), 1024.0f / 768.0f, 0.1f, 100.0f)), translation(1.0f), rotation(1.0f) {
  calc_view_mat();
}

Camera::Camera(float fovy, float aspect, float near, float far)
  : projection(glm::perspective(fovy, aspect, near, far)), translation(1.0f), rotation(1.0f) {
  calc_view_mat();
}

void Camera::translate(float delta_x, float delta_y, float delta_z) {
  translation = glm::translate(translation, glm::vec3(delta_x, delta_y, delta_z));
  calc_view_mat();
}

void Camera::rotate_x(float delta_theta) {
  rotation = glm::rotate(rotation, delta_theta, glm::vec3(1.0f, 0.0f, 0.0f));
  calc_view_mat();
}

void Camera::rotate_y(float delta_theta) {
  rotation = glm::rotate(rotation, delta_theta, glm::vec3(0.0f, 1.0f, 0.0f));
  calc_view_mat();
}

void Camera::set_translation(float x, float y, float z) {
  translation = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
  calc_view_mat();
}

void Camera::set_rotation_x(float theta) {
  rotation = glm::rotate(glm::mat4(1.0f), theta, glm::vec3(1.0f, 0.0f, 0.0f));
  calc_view_mat();
}

void Camera::set_rotation_y(float theta) {
  rotation = glm::rotate(glm::mat4(1.0f), theta, glm::vec3(0.0f, 1.0f, 0.0f));
  calc_view_mat();
}

void Camera::calc_view_mat() {
  view = glm::inverse(translation * rotation);
}
