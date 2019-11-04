#ifndef SOFTRD_MATH_PLANE_H_
#define SOFTRD_MATH_PLANE_H_

namespace softrd {

struct Plane {
	float a, b, c, d;

	Plane(const float a, const float b, const float c, const float d) : a(a), b(b), c(c), d(d) {}
};


} // namespace softrd



#endif // SOFTRD_MATH_PLANE_H_