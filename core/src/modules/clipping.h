#ifndef SOFTRD_CLIPPING_H_
#define SOFTRD_CLIPPING_H_

#include "src/common/primitive.h"
#include "src/math/math_util.h"

namespace softrd {

class Clipper {
 public:
  Clipper();

  static bool ClipLineNegativeW(LinePrimitive *line);
  static bool ClipLine(LinePrimitive *line);
  static bool OutsideViewFrustum(const math::vec4 &position);
  static bool BehindEyePoint(const math::vec4 &position);

 private:
  static int RegionCode(const math::vec4 &position);
  static bool CalcPerspectiveLineIntersection(const int code,
                                              const math::vec4 &p1,
                                              const math::vec4 &p2,
                                              math::vec4 *result);
};

}  // namespace softrd

#endif  // SOFTRD_CLIPPING_H_