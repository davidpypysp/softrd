#ifndef SOFTRD_MATH_MATH_LIB_H_
#define SOFTRD_MATH_MATH_LIB_H_

#define _USE_MATH_DEFINES
#include <math.h>

#include "matrix.h"
#include "vector.h"

namespace softrd {
inline float DegreeToRadian(const float angle) { return angle * (M_PI / 180.0); }
}


#endif // SOFTRD_MATH_MATH_LIB_H_