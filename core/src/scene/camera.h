#ifndef SOFTRD_CAMERA_H_
#define SOFTRD_CAMERA_H_

#include "src/math/math_util.h"

namespace softrd {
namespace scene {

class Camera {
 public:
  Camera(const float aspect) {
    /*
    position = math::vec3(0.0, 0.0, 3.0);
    direction_ = math::vec3(0.0, 0.0, 1.0);
    up = math::vec3(0.0, 1.0, 0.0);
    right = math::vec3(1.0, 0.0, 0.0);
    pitch = 0.0;
    yaw = 90.0;
    */
    position_ = math::vec3(6.0, 6.0, 10.0);
    pitch = 30.0;
    yaw = 60.0;

    direction_ = math::vec3(0.0, 0.0, 0.0);
    up = math::vec3(0.0, 1.0, 0.0);
    right = math::vec3(1.0, 0.0, 0.0);
    world_up = math::vec3(0.0, 1.0, 0.0);
    fov = 45.0;
    this->aspect = aspect;
    near_ = 0.2f;
    far_ = 500.0f;
    SetViewMatrix();
    SetProjectionMatrix();

    this->Rotate(math::vec3(0, 0, 0));
  }

  void SetViewMatrix() {
    view_ = {
        right.x,      right.y,      right.z,      -(right * position_),
        up.x,         up.y,         up.z,         -(up * position_),
        direction_.x, direction_.y, direction_.z, -(direction_ * position_),
        0.0,          0.0,          0.0,          1.0};
  }

  void SetProjectionMatrix() {
    float cot_theta = 1.0 / tan(math::Radians(fov * 0.5));
    projection_[0][0] = cot_theta / aspect;
    projection_[1][1] = cot_theta;
    projection_[2][2] = (far_ + near_) / (near_ - far_);
    projection_[2][3] = (2.0 * far_ * near_) / (near_ - far_);
    projection_[3][2] = -1.0;
  }

  void Move(const math::vec3 &move) {  // move: step
    position_ = position_ + right * move.x;
    position_ = position_ + up * move.y;
    position_ = position_ + direction_ * move.z;
    SetViewMatrix();
  }

  void Rotate(const math::vec3 &rotate) {  // x: pitch, y: yaw, z: roll(not use)
    pitch += rotate.x;
    yaw += rotate.y;
    if (pitch > 89.0)
      pitch = 89.0;
    else if (pitch < -89.0)
      pitch = -89.0;
    // if (yaw > 89.0) yaw = 89.0;
    // else if (yaw < -89.0) yaw = -89.0;

    direction_.x = cos(math::Radians(pitch)) * cos(math::Radians(yaw));
    direction_.y = sin(math::Radians(pitch));
    direction_.z = cos(math::Radians(pitch)) * sin(math::Radians(yaw));
    direction_.Normalize();
    right = (world_up % direction_).Normalize();
    up = (direction_ % right).Normalize();
    SetViewMatrix();
  }

  void Zoom(const float degree) {
    fov += degree;
    if (fov > 160.0) fov = 160.0;
    if (fov < 10.0) fov = 10.0;
    SetProjectionMatrix();
  }

  math::vec3 *PositionPtr() { return &position_; }

  math::vec3 position() { return position_; }
  math::vec3 direction() { return direction_; }

  float far() const { return far_; }
  float near() const { return near_; }

  math::mat4 view() const { return view_; }
  math::mat4 projection() const { return projection_; }

 private:
  math::vec3 position_;
  math::vec3 direction_;
  math::vec3 up;
  math::vec3 right;
  math::vec3 world_up;

  float pitch;
  float yaw;
  float fov;  // degree in y direction_
  float aspect;

  float near_;
  float far_;

  math::mat4 view_;
  math::mat4 projection_;
};

}  // namespace scene
}  // namespace softrd

#endif  // SOFTRD_CAMERA_H_