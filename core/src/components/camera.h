#ifndef SOFTRD_CAMERA_H_
#define SOFTRD_CAMERA_H_

#include "src/math/math_util.h"

namespace softrd {

struct Camera {
  math::vec3 position;
  math::vec3 direction;
  math::vec3 up;
  math::vec3 right;
  math::vec3 world_up;
  float pitch;
  float yaw;
  float fov;  // degree in y direction
  float aspect;
  float near, far;
  math::mat4 view;
  math::mat4 projection;

  Camera(const float aspect) {
    /*
    position = math::vec3(0.0, 0.0, 3.0);
    direction = math::vec3(0.0, 0.0, 1.0);
    up = math::vec3(0.0, 1.0, 0.0);
    right = math::vec3(1.0, 0.0, 0.0);
    pitch = 0.0;
    yaw = 90.0;
    */
    position = math::vec3(6.0, 6.0, 10.0);
    pitch = 30.0;
    yaw = 60.0;

    direction = math::vec3(0.0, 0.0, 0.0);
    up = math::vec3(0.0, 1.0, 0.0);
    right = math::vec3(1.0, 0.0, 0.0);
    world_up = math::vec3(0.0, 1.0, 0.0);
    fov = 45.0;
    this->aspect = aspect;
    near = 0.2f;
    far = 500.0f;
    SetViewMatrix();
    SetProjectionMatrix();

    this->Rotate(math::vec3(0, 0, 0));
  }

  void SetViewMatrix() {
    view = {right.x,     right.y,     right.z,     -(right * position),
            up.x,        up.y,        up.z,        -(up * position),
            direction.x, direction.y, direction.z, -(direction * position),
            0.0,         0.0,         0.0,         1.0};
  }

  void SetProjectionMatrix() {
    float cot_theta = 1.0 / tan(math::Radians(fov * 0.5));
    projection[0][0] = cot_theta / aspect;
    projection[1][1] = cot_theta;
    projection[2][2] = (far + near) / (near - far);
    projection[2][3] = (2.0 * far * near) / (near - far);
    projection[3][2] = -1.0;
  }

  void Move(const math::vec3 &move) {  // move: step
    position = position + right * move.x;
    position = position + up * move.y;
    position = position + direction * move.z;
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

    direction.x = cos(math::Radians(pitch)) * cos(math::Radians(yaw));
    direction.y = sin(math::Radians(pitch));
    direction.z = cos(math::Radians(pitch)) * sin(math::Radians(yaw));
    direction.Normalize();
    right = (world_up % direction).Normalize();
    up = (direction % right).Normalize();
    SetViewMatrix();
  }

  void Zoom(const float degree) {
    fov += degree;
    if (fov > 160.0) fov = 160.0;
    if (fov < 10.0) fov = 10.0;
    SetProjectionMatrix();
  }
};

}  // namespace softrd

#endif  // SOFTRD_CAMERA_H_