#ifndef SOFTRD_MATH_MATH_LIB_H_
#define SOFTRD_MATH_MATH_LIB_H_

#define _USE_MATH_DEFINES
#include <math.h>

#include "matrix.h"
#include "vector.h"

namespace softrd {

inline float Radians(const float angle) { return angle * (M_PI / 180.0); }
	
template <class T> 
inline void Swap(T &t1, T &t2) {
	T temp = t1;
	t1 = t2;
	t2 = temp;
}

inline float Clamp(const float value, const float min, const float max) {
	if (value > max) return max;
	if (value < min) return min;
	return value;
}

inline int ArrayIndex(const int x, const int y, const int col) {
	return x + y * col;
}


inline float LinearInterpolationCoef(const float x1, const float x2, const float x) {
	return (x - x1) / (x2 - x1);
}


template<typename T>
inline T LinearInterpolation(const T &a, const T &b, const float k) { // T could be float, vec3, vec4, mat3, mat4 ...
	return (1 - k) * a + k * b;
}


inline vec3 BarycentricCoordinates(const vec2 &a, const vec2 &b, const vec2 &c, const vec2 &p) {
	/*
	mat3 m_abc = {
	1, a.x, a.y,
	1, b.x, b.y,
	1, c.x, c.y,
	};
	mat3 m_pbc = {
	1, p.x, p.y,
	1, b.x, b.y,
	1, c.x, c.y,
	};
	mat3 m_pca = {
	1, p.x, p.y,
	1, c.x, c.y,
	1, a.x, a.y,
	};
	mat3 m_pab = {
	1, p.x, p.y,
	1, a.x, a.y,
	1, b.x, b.y,
	};
	float det_abc = m_abc.det();
	float det_pbc = m_pbc.det();
	float det_pca = m_pca.det();
	float det_pab = m_pab.det();
	*/

	float det_abc = b.x * c.y + a.x * b.y + a.y * c.x - b.x * a.y - c.x * b.y - c.y * a.x;
	float det_pbc = b.x * c.y + p.x * b.y + p.y * c.x - b.x * p.y - c.x * b.y - c.y * p.x;
	float det_pca = c.x * a.y + p.x * c.y + p.y * a.x - c.x * p.y - a.x * c.y - a.y * p.x;
	float det_pab = a.x * b.y + p.x * a.y + p.y * b.x - a.x * p.y - b.x * a.y - b.y * p.x;

	return vec3(det_pbc / det_abc, det_pca / det_abc, det_pab / det_abc);
}

template<typename T>
inline T TriangleInterpolation(const T &a, const T &b, const T &c, const vec3 &k) { // T could be float, vec3, vec4, mat3, mat4 ...
	return k.x * a + k.y * b + k.z * c;
}

inline float Max(const float a, const float b) {
	return a > b ? a : b;
}


} // namespace softrd


#endif // SOFTRD_MATH_MATH_LIB_H_