#ifndef SOFTRD_LIGHT_H_
#define SOFTRD_LIGHT_H_

#include "math/vector.h"

namespace softrd {

struct Light {
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	Light(const vec3 &position = vec3(), const vec3 &ambient = vec3(), const vec3 &diffuse = vec3(), const vec3 &specular = vec3()) :
		position(position),
		ambient(ambient),
		diffuse(diffuse),
		specular(specular) {
	}


};


} // namespace softrd




#endif // SOFTRD_LIGHT_H_