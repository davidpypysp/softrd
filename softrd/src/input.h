#ifndef SOFTRD_INPUT_H_
#define SOFTRD_INPUT_H_

#include <iostream>

#include "math/vector.h"

namespace softrd {

struct InputUnit {
	std::string name;
	vec3 *position;

	InputUnit(std::string name, vec3 *position) : name(name), position(position) {}
};

} // namespace softrd

#endif // SOFTRD_INPUT_H_