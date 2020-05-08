#include "src/common/texture.h"

#include <glog/logging.h>

namespace softrd {

//  texture coordinate sample
//  (0.0, 0.0); // left, up
//  (0.0, 1.0); // left, down
//  (1.0, 0.0); // right, up
//  (1.0, 1.0); // right, down

Texture::Texture(const char *file_name) {
  unsigned char *image =
      SOIL_load_image(file_name, &width_, &height_, 0, SOIL_LOAD_RGB);

  if (image == nullptr) {
    LOG(WARNING) << "Can not get image: " << file_name;
    return;
  }

  LOG(INFO) << "Loaded image: " << file_name << ", width: " << width_
            << ", height: " << height_;
  pixels_ = new math::vec3[width_ * height_];

  float k = 1.0 / 255.0;
  for (int i = 0; i < width_ * height_; i++) {
    pixels_[i].x = image[i * 3] * k;
    pixels_[i].y = image[i * 3 + 1] * k;
    pixels_[i].z = image[i * 3 + 2] * k;
  }
  SOIL_free_image_data(image);
}

math::vec3 Texture::GetColor(const float u, const float v) {
  // bounds-test u,v to make sure nothing will overflow image array bounds
  float x = math::Clamp(u, 0.0, 1.0) * (width_ - 1);
  float y = math::Clamp(v, 0.0, 1.0) * (height_ - 1);

  // determine texture cell corner values and perform bilinear interpolation
  int left = floor(x), right = ceil(x), up = floor(y), down = floor(y);
  math::vec3 &lu = pixels_[math::ArrayIndex(left, up, width_)];
  math::vec3 &ru = pixels_[math::ArrayIndex(right, up, width_)];
  math::vec3 &rd = pixels_[math::ArrayIndex(right, down, width_)];
  math::vec3 &ld = pixels_[math::ArrayIndex(left, down, width_)];

  float kx = x - left, ky = y - up;
  math::vec3 color = rd * kx * ky + ld * (1 - kx) * ky + ru * kx * (1 - ky) +
                     lu * (1 - kx) * (1 - ky);
  return color;
}

math::vec3 Texture::GetColor(const math::vec2 &uv) {
  return GetColor(uv.x, uv.y);
}
}  // namespace softrd