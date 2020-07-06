#include "src/modules/clipping.h"

namespace softrd {

#define W_ZERO 0.001  // for negative w clipping

// for Cohen-Sutherland algorithm
#define REGION_BL 1
#define REGION_BR 2
#define REGION_BB 4
#define REGION_BT 8
#define REGION_BN 16
#define REGION_BF 32

Clipper::Clipper() {}

bool Clipper::ClipLineNegativeW(
    LinePrimitive *line) {  // false if need to discard this line
  int negative_num = 0;
  int index = 0;
  for (int i = 0; i < 2; i++) {
    if (line->vertex_out[i].position.w < W_ZERO) {
      index = i;
      negative_num++;
    }
  }

  if (negative_num == 0) return true;
  if (negative_num == 2) return false;

  float k = math::LinearInterpolationCoef(
      line->vertex_out[0].position.w, line->vertex_out[1].position.w, W_ZERO);
  math::vec4 position = LinearInterpolation(line->vertex_out[0].position,
                                            line->vertex_out[1].position, k);
  line->vertex_out[index].position = position;
  return true;
}

bool Clipper::ClipLine(LinePrimitive *line) {  // Cohen - Sutherland algorithm
  math::vec4 p[] = {line->vertex_out[0].position, line->vertex_out[1].position};
  int codes[] = {RegionCode(p[0]), RegionCode(p[1])};

  if (codes[0] == 0 && codes[1] == 0)
    return true;  // both in view frustum. No need to clip
  if (codes[0] & codes[1])
    return false;  // both outside and not get through view frustum. Discard.

  for (int i = 0; i < 2; ++i) {
    math::vec4 clip_position;
    if (codes[i] != 0) {
      if (CalcPerspectiveLineIntersection(codes[i], p[0], p[1],
                                          &clip_position) == false)
        return false;
      line->vertex_out[i].position = clip_position;
    }
  }
  return true;
}

bool Clipper::OutsideViewFrustum(
    const math::vec4 &position) {  // if position is out of frustum
  /*
  if (position.x <= -position.w || position.x >= position.w) return true;
  if (position.y <= -position.w || position.y >= position.w) return true;
  if (position.z <= -position.w || position.z >= position.w) return true;
  return false;
  */

  // loose way
  if (position.x >= -position.w && position.x <= position.w) return false;
  if (position.y >= -position.w && position.y <= position.w) return false;
  if (position.z >= -position.w && position.z <= position.w) return false;
  return true;
}

bool Clipper::BehindEyePoint(const math::vec4 &position) {
  return position.w <= 0;
}

int Clipper::RegionCode(
    const math::vec4 &position) {  // Cohen-Sutherland algorithm
  int code = 0;
  if (position.x < -position.w)
    code |= REGION_BL;
  else if (position.x > position.w)
    code |= REGION_BR;

  if (position.y < -position.w)
    code |= REGION_BB;
  else if (position.y > position.w)
    code |= REGION_BT;

  if (position.z < -position.w)
    code |= REGION_BN;
  else if (position.z > position.w)
    code |= REGION_BF;

  return code;
}

bool Clipper::CalcPerspectiveLineIntersection(const int code,
                                              const math::vec4 &p1,
                                              const math::vec4 &p2,
                                              math::vec4 *result) {
  float a = 0.0;
  math::vec4 p;
  if (code & REGION_BL) {
    a = (p1.w + p1.x) / ((p1.w + p1.x) - (p2.w + p2.x));
    p = LinearInterpolation(p1, p2, a);
    if (p.y >= -p.w && p.y <= p.w && p.z >= -p.w && p.z <= p.w) {
      *result = p;
      return true;
    }
  } else if (code & REGION_BR) {
    a = (p1.w - p1.x) / ((p1.w - p1.x) - (p2.w - p2.x));
    p = LinearInterpolation(p1, p2, a);
    if (p.y >= -p.w && p.y <= p.w && p.z >= -p.w && p.z <= p.w) {
      *result = p;
      return true;
    }
  }

  if (code & REGION_BB) {
    a = (p1.w + p1.y) / ((p1.w + p1.y) - (p2.w + p2.y));
    p = LinearInterpolation(p1, p2, a);
    if (p.x >= -p.w && p.x <= p.w && p.z >= -p.w && p.z <= p.w) {
      *result = p;
      return true;
    }
  } else if (code & REGION_BT) {
    a = (p1.w - p1.y) / ((p1.w - p1.y) - (p2.w - p2.y));
    p = LinearInterpolation(p1, p2, a);
    if (p.x >= -p.w && p.x <= p.w && p.z >= -p.w && p.z <= p.w) {
      *result = p;
      return true;
    }
  }

  if (code & REGION_BN) {
    a = (p1.w + p1.z) / ((p1.w + p1.z) - (p2.w + p2.z));
    p = LinearInterpolation(p1, p2, a);
    if (p.x >= -p.w && p.x <= p.w && p.y >= -p.w && p.y <= p.w) {
      *result = p;
      return true;
    }
  } else if (code & REGION_BF) {
    a = (p1.w - p1.z) / ((p1.w - p1.z) - (p2.w - p2.z));
    p = LinearInterpolation(p1, p2, a);
    if (p.x >= -p.w && p.x <= p.w && p.y >= -p.w && p.y <= p.w) {
      *result = p;
      return true;
    }
  }

  return false;  // no intersection with view frustum
}

}  // namespace softrd
