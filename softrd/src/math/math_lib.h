#ifndef SOFTRD_MATH_MATH_LIB_H_
#define SOFTRD_MATH_MATH_LIB_H_

#define _USE_MATH_DEFINES
#include <math.h>

#include "matrix.h"
#include "vector.h"

namespace softrd {

inline float Radians(const float angle) { return angle * (M_PI / 180.0); }
	
template <class T> 
void Swap(T &t1, T &t2) {
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


} // namespace softrd


#endif // SOFTRD_MATH_MATH_LIB_H_