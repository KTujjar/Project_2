#include "renderer/camera.h"

#include <glm/gtc/matrix_transform.hpp>   // glm::lookAt, glm::perspective
#include <algorithm>                      // std::clamp
#include <cmath>                          // std::sin, std::cos

Camera::Camera(float aspect){
    this->yaw = 0.0f;
    this->pitch = 0.3f;     // slight downward tilt so the cloud reads as 3D
    this->radius = 3.0f;
    this->aspect = aspect;
}

glm::mat4 Camera::view() const{
    // spherical -> cartesian: pitch lifts off the equator, yaw walks the ring
    glm::vec3 eye(
        radius * std::cos(pitch) * std::sin(yaw),
        radius * std::sin(pitch),
        radius * std::cos(pitch) * std::cos(yaw));
    return glm::lookAt(eye, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::mat4 Camera::projection() const{
    return glm::perspective(glm::radians(45.0f), aspect, 0.1f, 100.0f);
}

void Camera::rotate(float yaw_delta, float pitch_delta){
    yaw += yaw_delta;
    // stop just short of +/-90 deg or lookAt's up vector degenerates
    pitch = std::clamp(pitch + pitch_delta, -1.5f, 1.5f);
}

void Camera::zoom(float radius_delta){
    radius = std::clamp(radius + radius_delta, 0.5f, 50.0f);
}

void Camera::set_aspect(float aspect){
    this->aspect = aspect;
}
