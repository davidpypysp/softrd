#ifndef SOFTRD_INPUT_H_
#define SOFTRD_INPUT_H_

#include <iostream>

#include "src/math/vector.h"

namespace softrd {

struct InputUnit {
public:
	std::string name;
	int size;
	
	InputUnit(std::string name, int size) : name(name), size(size) {}

	virtual void Move(const vec4 &move) = 0;
	virtual std::string Info(int precision = 2) = 0;

};

struct InputUnit1 : public InputUnit {
	float *value;


	InputUnit1(std::string name, float *value) : InputUnit(name, 1), value(value) {
	}

	void Move(const vec4 &move) {
		*value += move.z;
	}


	std::string Info(int precision) {
		return name + ": " + util::ToString(*value, precision);
	}
};

struct InputUnit2 : public InputUnit {
	vec2 *value;

	InputUnit2(std::string name, vec2 *value) : InputUnit(name, 2) , value(value) {
	}

	void Move(const vec4 &move) {
		value->move(vec2(move.z, move.x));
	}

	std::string Info(int precision) {
		return name + ": ("
			+ util::ToString(value->x, precision) + ", "
			+ util::ToString(value->y, precision) + ")";
	}

};

struct InputUnit3 : public InputUnit {
	vec3 *value;

	InputUnit3(std::string name, vec3 *value) : InputUnit(name, 3), value(value) {
	}

	void Move(const vec4 &move) {
		value->move(vec3(move.x, move.y, move.z));
	}

	std::string Info(int precision) {
		return name + ": ("
			+ util::ToString(value->x, precision) + ", "
			+ util::ToString(value->y, precision) + ", "
			+ util::ToString(value->z, precision) + ")";
	}
};

struct InputUnit4 : public InputUnit {
	vec4 *value;

	InputUnit4(std::string name, vec4 *value) : InputUnit(name, 4), value(value) {
	}

	void Move(const vec4 &move) {
		value->move(move);
	}


	std::string Info(int precision) {
		return name + ": ("
			+ util::ToString(value->x, precision) + ", "
			+ util::ToString(value->y, precision) + ", "
			+ util::ToString(value->z, precision) + ","
			+ util::ToString(value->w, precision) + ")";
	}
};

} // namespace softrd

#endif // SOFTRD_INPUT_H_