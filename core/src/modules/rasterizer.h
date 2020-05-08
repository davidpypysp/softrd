#ifndef SOFTRD_RASTERIZER_H_
#define SOFTRD_RASTERIZER_H_

#include <vector>

#include "src/common/fragment.h"
#include "src/math/math_util.h"
#include "src/modules/primitive_assembly.h"
#include "src/scene/camera.h"

namespace softrd {

class Rasterizer {
 public:
  enum DrawMode { DRAW_LINE, DRAW_TRIANGLE };
  enum DrawTriangleMode { TRIANGLE_FILL, TRIANGLE_LINE };

  Rasterizer(const int width, const int height,
             std::vector<Fragment> &fragment_buffer);
  void SetCamera(scene::Camera *camera);

  void DrawLinePrimitive(const LinePrimitive &line);
  // draw triangle on window space by scan-line algorithm
  void DrawTrianglePrimitive(const TrianglePrimitive &triangle,
                             DrawTriangleMode mode);

 private:
  void DrawTriangleScanLine(const TrianglePrimitive &triangle);
  void DrawFlatBottomTriangle(const math::vec3 &bottom_position1,
                              const math::vec3 &bottom_position2,
                              const math::vec3 &top_position);
  void DrawFlatTopTriangle(const math::vec3 &bottom_position,
                           const math::vec3 &top_position1,
                           const math::vec3 &top_position2,
                           bool draw_top_integer_line);
  void DrawScanLine(const float x1, const float x2, const float y);
  void LineGenerateFragment(const float x, const float y);
  void TriangleGenerateFragment(const float x, const float y);
  void DrawLine(const math::vec2 &position1, const math::vec2 &position2);
  void InitTriangleInterpolation(const TrianglePrimitive &triangle);
  void InitLineInterpolation(const LinePrimitive &line);

  int width_, height_;
  std::vector<Fragment> &fragment_buffer_;
  scene::Camera *camera_;

  DrawMode draw_mode_;
  LinePrimitive line_;
  TrianglePrimitive triangle_;  // for triangle interpolation
  math::vec2 positions_[3];     // for interpolation
  float perspective_k_;         // for perspective texture mapping
  math::vec2 wrapped_uvs[3];
};

}  // namespace softrd

#endif  // SOFTRD_RASTERIZER_H_