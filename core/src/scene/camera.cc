#include "src/scene/camera.h"

namespace softrd {
namespace scene {

Camera::Camera(const math::vec3 &position, const float aspect) {
  position_ = position;
  direction_ = (position_ - math::vec3(0.0, 0.0, 0.0)).Normalize();
  right_ = (world_up_ % direction_).Normalize();
  up_ = (direction_ % right_).Normalize();

  pitch_ = 30.0;
  yaw_ = 60.0;

  fov_ = 45.0;
  aspect_ = aspect;
  near_ = 0.2;
  far_ = 500.0;

  SetViewMatrix();
  SetProjectionMatrix();
}

void Camera::SetViewMatrix() {
  view_ = {right_.x,     right_.y,     right_.z,     -(right_ * position_),
           up_.x,        up_.y,        up_.z,        -(up_ * position_),
           direction_.x, direction_.y, direction_.z, -(direction_ * position_),
           0.0,          0.0,          0.0,          1.0};
}

void Camera::SetProjectionMatrix() {
  float cot_theta = 1.0 / tan(math::Radians(fov_ * 0.5));
  projection_[0][0] = cot_theta / aspect_;
  projection_[1][1] = cot_theta;
  projection_[2][2] = (far_ + near_) / (near_ - far_);
  projection_[2][3] = (2.0 * far_ * near_) / (near_ - far_);
  projection_[3][2] = -1.0;
}

void Camera::Move(const math::vec3 &move) {
  // move: step
  position_ = position_ + right_ * move.x;
  position_ = position_ + up_ * move.y;
  position_ = position_ + direction_ * move.z;
  SetViewMatrix();
}

void Camera::Rotate(const math::vec3 &rotate) {
  // x: pitch, y: yaw, z: roll(not use)
  pitch_ += rotate.x;
  yaw_ += rotate.y;
  if (pitch_ > 89.0) {
    pitch_ = 89.0;
  } else if (pitch_ < -89.0) {
    pitch_ = -89.0;
  }
  // if (yaw > 89.0) yaw = 89.0;
  // else if (yaw < -89.0) yaw = -89.0;

  direction_.x = cos(math::Radians(pitch_)) * cos(math::Radians(yaw_));
  direction_.y = sin(math::Radians(pitch_));
  direction_.z = cos(math::Radians(pitch_)) * sin(math::Radians(yaw_));
  direction_.Normalize();

  right_ = (world_up_ % direction_).Normalize();
  up_ = (direction_ % right_).Normalize();

  SetViewMatrix();
}

void Camera::Zoom(const float degree) {
  fov_ += degree;
  if (fov_ > 160.0) {
    fov_ = 160.0;
  }
  if (fov_ < 10.0) {
    fov_ = 10.0;
  }
  SetProjectionMatrix();
}

}  // namespace scene
}  // namespace softrd