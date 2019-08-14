#ifndef SOFTRD_CLIPPING_H_
#define SOFTRD_CLIPPING_H_

#include "primitive.h"
#include "math/math_lib.h"

namespace softrd {

class Clipper {
public:
	Clipper();

	static bool ClipLineNegativeW(LinePrimitive *line);
	static bool ClipLine(LinePrimitive *line);
	static bool OutsideViewFrustum(const vec4 &position);
	static bool BehindEyePoint(const vec4 &position);

private:
	static int RegionCode(const vec4 &position);
	static bool CalcPerspectiveLineIntersection(const int code, const vec4 &p1, const vec4 &p2, vec4 *result);

};

} // namespace softrd

#endif // SOFTRD_CLIPPING_H_