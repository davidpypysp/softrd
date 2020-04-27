#ifndef SOFTRD_TEXTURE_H_
#define SOFTRD_TEXTURE_H_

#include <include/SOIL/SOIL.h>

#include "src/math/math_util.h"

namespace softrd {

class Texture {
 public:
  explicit Texture(const char *file_name);
  ~Texture() { delete[] pixels_; }

  math::vec3 GetColor(const float u, const float v);
  math::vec3 GetColor(const math::vec2 &uv);

 private:
  int width_;
  int height_;
  math::vec3 *pixels_;
};

}  // namespace softrd

#endif  // SOFTRD_TEXTURE_H_