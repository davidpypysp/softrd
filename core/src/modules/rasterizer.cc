#include "src/modules/rasterizer.h"

namespace softrd {
Rasterizer::Rasterizer(const int width, const int height,
                       std::vector<Fragment> &fragment_buffer)
    : width_(width), height_(height), fragment_buffer_(fragment_buffer) {}

void Rasterizer::SetCamera(Camera *camera) { camera_ = camera; }

void Rasterizer::DrawLinePrimitive(const LinePrimitive &line) {
  draw_mode_ = DRAW_LINE;
  fragment_buffer_.clear();
  InitLineInterpolation(line);

  math::vec2 position1(line.v[0].position.x, line.v[0].position.y);
  math::vec2 position2(line.v[1].position.x, line.v[1].position.y);
  DrawLine(position1, position2);
}

void Rasterizer::DrawTrianglePrimitive(
    const TrianglePrimitive &triangle,
    DrawTriangleMode mode) {  // scan line algorithm
  draw_mode_ = DRAW_TRIANGLE;
  fragment_buffer_.clear();
  InitTriangleInterpolation(triangle);

  if (mode == TRIANGLE_FILL) {
    DrawTriangleScanLine(triangle);
  } else if (mode == TRIANGLE_LINE) {  // draw 3 lines
    math::vec2 position0(triangle.v[0].position.x, triangle.v[0].position.y);
    math::vec2 position1(triangle.v[1].position.x, triangle.v[1].position.y);
    math::vec2 position2(triangle.v[2].position.x, triangle.v[2].position.y);
    DrawLine(position0, position1);
    DrawLine(position1, position2);
    DrawLine(position2, position0);
  }
}

void Rasterizer::DrawTriangleScanLine(const TrianglePrimitive &triangle) {
  // sorted 3 vertices
  int min_index = 0, max_index = 0;
  for (int i = 1; i < 3;
       i++) {  // find the index of max-y's position and min-y's position
    if ((triangle.v[i].position.y < triangle.v[min_index].position.y) ||
        (triangle.v[i].position.y == triangle.v[min_index].position.y &&
         triangle.v[i].position.x < triangle.v[min_index].position.x))
      min_index = i;
    if (triangle.v[i].position.y > triangle.v[max_index].position.y ||
        (triangle.v[i].position.y == triangle.v[max_index].position.y &&
         triangle.v[i].position.x > triangle.v[max_index].position.x))
      max_index = i;
  }

  math::vec3 bottom_position(triangle.v[min_index].position.x,
                             triangle.v[min_index].position.y,
                             triangle.v[min_index].position.z);
  math::vec3 middle_position(triangle.v[3 - max_index - min_index].position.x,
                             triangle.v[3 - max_index - min_index].position.y,
                             triangle.v[3 - max_index - min_index].position.z);
  math::vec3 top_position(triangle.v[max_index].position.x,
                          triangle.v[max_index].position.y,
                          triangle.v[max_index].position.z);

  if (bottom_position.y == top_position.y) {  // 3 positions in same line
    if (top_position.y == floorf(top_position.y))
      DrawScanLine(bottom_position.x, top_position.x, top_position.y);
  } else if (bottom_position.y ==
             middle_position.y) {  // it is flat bottom triangle
    DrawFlatBottomTriangle(bottom_position, middle_position, top_position);
  } else if (middle_position.y == top_position.y) {  // it is flat top triangle
    DrawFlatTopTriangle(bottom_position, middle_position, top_position, true);
  } else {  // seperate into flat bottom triangle and flat top triangle
    float middle_x2 =
        top_position.x - (top_position.y - middle_position.y) *
                             (top_position.x - bottom_position.x) /
                             (top_position.y - bottom_position.y);
    math::vec3 middle_position2(middle_x2, middle_position.y,
                                0.0);  // z value doesn't matter for now
    if (middle_position.x < middle_position2.x) {
      DrawFlatBottomTriangle(middle_position, middle_position2, top_position);
      DrawFlatTopTriangle(bottom_position, middle_position, middle_position2,
                          false);
    } else {
      DrawFlatBottomTriangle(middle_position2, middle_position, top_position);
      DrawFlatTopTriangle(bottom_position, middle_position2, middle_position,
                          false);
    }
  }
}

void Rasterizer::DrawFlatBottomTriangle(const math::vec3 &bottom_position1,
                                        const math::vec3 &bottom_position2,
                                        const math::vec3 &top_position) {
  float x_slope1 = (top_position.x - bottom_position1.x) /
                   (top_position.y - bottom_position1.y);
  float x_slope2 = (top_position.x - bottom_position2.x) /
                   (top_position.y - bottom_position2.y);
  float start_y = ceilf(bottom_position1.y);
  float x1 = bottom_position1.x + x_slope1 * (start_y - bottom_position1.y);
  float x2 = bottom_position2.x + x_slope2 * (start_y - bottom_position1.y);
  for (float y = start_y; y <= top_position.y; ++y) {
    DrawScanLine(x1, x2, y);
    x1 += x_slope1;
    x2 += x_slope2;
  }
}

void Rasterizer::DrawFlatTopTriangle(const math::vec3 &bottom_position,
                                     const math::vec3 &top_position1,
                                     const math::vec3 &top_position2,
                                     bool draw_top_integer_line) {
  float x_slope1 = (top_position1.x - bottom_position.x) /
                   (top_position1.y - bottom_position.y);
  float x_slope2 = (top_position2.x - bottom_position.x) /
                   (top_position2.y - bottom_position.y);
  float start_y = ceilf(bottom_position.y);
  float x1 = bottom_position.x + x_slope1 * (start_y - bottom_position.y);
  float x2 = bottom_position.x + x_slope2 * (start_y - bottom_position.y);
  for (float y = start_y; y < top_position1.y; ++y) {
    DrawScanLine(x1, x2, y);
    x1 += x_slope1;
    x2 += x_slope2;
  }
  if (draw_top_integer_line &&
      top_position1.y == floorf(top_position1.y)) {  // for special case
    DrawScanLine(x1, x2, top_position1.y);
  }
}

void Rasterizer::DrawScanLine(const float x1, const float x2, const float y) {
  for (float x = ceilf(x1); x <= x2; ++x) {
    TriangleGenerateFragment(x, y);
  }
}

void Rasterizer::LineGenerateFragment(const float x, const float y) {
  if (x < 0 || x >= width_ || y < 0 || y >= height_) return;

  // interpolation process
  float k = math::LinearInterpolationCoef(positions_[0].x, positions_[1].x, x);

  float z = math::LinearInterpolation(line_.v[0].position.z,
                                      line_.v[1].position.z, k);

  Fragment fragment;
  fragment.window_position = math::vec3(x, y, z);

  fragment_buffer_.push_back(fragment);
}

void Rasterizer::TriangleGenerateFragment(const float x, const float y) {
  if (x < 0 || x >= width_ || y < 0 || y >= height_) return;

  // interpolation process
  math::vec3 k = BarycentricCoordinates(positions_[0], positions_[1],
                                        positions_[2], math::vec2(x, y));

  Fragment fragment;

  float z = TriangleInterpolation(triangle_.v[0].position.z,
                                  triangle_.v[1].position.z,
                                  triangle_.v[2].position.z, k);
  fragment.window_position = math::vec3(x, y, z);

  // lighting
  fragment.world_position = TriangleInterpolation(
      triangle_.v[0].world_position, triangle_.v[1].world_position,
      triangle_.v[2].world_position, k);
  fragment.world_normal = TriangleInterpolation(triangle_.v[0].world_normal,
                                                triangle_.v[1].world_normal,
                                                triangle_.v[2].world_normal, k);

  // perspective texture mapping
  fragment.uv =
      TriangleInterpolation(wrapped_uvs[0], wrapped_uvs[1], wrapped_uvs[2], k) /
      (z - perspective_k_);

  fragment_buffer_.push_back(fragment);
}

void Rasterizer::DrawLine(
    const math::vec2 &position1,
    const math::vec2 &position2) {  // Bresenham's line algorithm
  int x1 = roundf(position1.x), y1 = roundf(position1.y);
  int x2 = roundf(position2.x), y2 = roundf(position2.y);
  bool steep = abs(y1 - y2) > abs(x1 - x2);
  if (steep) {
    math::Swap(x1, y1);
    math::Swap(x2, y2);
  }
  if (x1 > x2) {
    math::Swap(x1, x2);
    math::Swap(y1, y2);
  }

  int dx = x2 - x1;
  int dy = abs(y2 - y1);
  int error = -dx;
  int delta_error = 2 * dy, reset_error = 2 * dx;
  int y = y1;
  int y_step = y1 < y2 ? 1 : -1;
  for (int x = x1; x <= x2; x++) {
    math::vec2 position(x, y);
    if (steep) {
      position.x = y;
      position.y = x;
    }
    if (position.x >= 0 && position.x < width_ && position.y >= 0 &&
        position.y < height_) {
      if (draw_mode_ == DRAW_LINE) {
        LineGenerateFragment(position.x, position.y);
      } else if (draw_mode_ == DRAW_TRIANGLE) {
        TriangleGenerateFragment(position.x, position.y);
      }
    }

    error += delta_error;
    if (error > 0) {
      y += y_step;
      error -= reset_error;
    }
  }
}

void Rasterizer::InitTriangleInterpolation(const TrianglePrimitive &triangle) {
  triangle_ = triangle;
  for (int i = 0; i < 3; ++i) {
    positions_[i].x = triangle_.v[i].position.x;
    positions_[i].y = triangle_.v[i].position.y;

    // for perspective texture mapping
    perspective_k_ = camera_->far / (camera_->far - camera_->near);
    wrapped_uvs[i].x =
        triangle_.v[i].uv.x * (triangle_.v[i].position.z - perspective_k_);
    wrapped_uvs[i].y =
        triangle_.v[i].uv.y * (triangle_.v[i].position.z - perspective_k_);

    // wrapped_uvs[i].x = triangle_.v[i].uv.x ;
    // wrapped_uvs[i].y = triangle_.v[i].uv.y ;
  }
}

void Rasterizer::InitLineInterpolation(const LinePrimitive &line) {
  line_ = line;
  for (int i = 0; i < 2; ++i) {
    positions_[i].x = line_.v[i].position.x;
  }
}

}  // namespace softrd
