#ifndef SOFTRD_FRAGMENT_H_
#define SOFTRD_FRAGMENT_H_

#include "math/vector.h"


namespace softrd {

struct Fragment {
	vec3 window_position;
	vec3 world_position;
	vec3 world_normal;
	vec2 uv;

};

} // namespace softrd

#endif // SOFTRD_FRAGMENT_H_