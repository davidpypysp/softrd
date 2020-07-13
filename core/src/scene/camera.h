#ifndef SOFTRD_CAMERA_H_
#define SOFTRD_CAMERA_H_

#include "src/math/math_util.h"
#include "src/scene/base_object.h"

namespace softrd {
namespace scene {

class Camera : public BaseObject {
 public:
  Camera(const math::vec3 &position, const float aspect);

  void SetViewMatrix();
  void SetProjectionMatrix();
  void Move(const math::vec3 &move);
  void Rotate(const math::vec3 &rotation);
  void Zoom(const float degree);

  math::vec3 *PositionPtr() { return &position_; }

  math::vec3 direction() { return direction_; }

  float far() const { return far_; }
  float near() const { return near_; }

  math::mat4 view() const { return view_; }
  math::mat4 projection() const { return projection_; }

 private:
  math::vec3 direction_;  // direction towards the point camera look at
  math::vec3 up_;
  math::vec3 right_;

  const math::vec3 world_up_ =
      math::vec3(0.0, 1.0, 0.0);  // static world up direction

  float pitch_;
  float yaw_;
  float fov_;  // degree in y direction_
  float aspect_;

  float near_;
  float far_;

  math::mat4 view_;
  math::mat4 projection_;
};

}  // namespace scene
}  // namespace softrd

#endif  // SOFTRD_CAMERA_H_