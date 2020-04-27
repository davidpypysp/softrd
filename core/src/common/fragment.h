#ifndef SOFTRD_FRAGMENT_H_
#define SOFTRD_FRAGMENT_H_

#include "src/math/vector.h"

namespace softrd {

struct Fragment {
  math::vec3 window_position;
  math::vec3 world_position;
  math::vec3 world_normal;
  math::vec2 uv;
};

}  // namespace softrd

#endif  // SOFTRD_FRAGMENT_H_