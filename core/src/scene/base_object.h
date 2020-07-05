#ifndef SOFTRD_BASE_OBJECT_H_
#define SOFTRD_BASE_OBJECT_H_

#include "src/math/vector.h"

namespace softrd {

namespace scene {

class BaseObject {
 public:
  void set_id(const std::string &id) { id_ = id; }
  std::string id() const { return id_; }

  void set_position(const math::vec3 &position) { position_ = position; }
  math::vec3 position() const { return position_; }

  void set_rotation(const math::vec3 &rotation) { rotation_ = rotation; }
  math::vec3 rotation() const { return rotation_; }

 protected:
  std::string id_;

  math::vec3 position_;
  math::vec3 rotation_;
};

} // namespace scene

}  // namespace softrd

#endif  // SOFTRD_BASE_OBJECT_H_