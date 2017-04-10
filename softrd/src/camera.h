#ifndef SOFTRD_CAMERA_H_
#define SOFTRD_CAMERA_H_

#include "math/math_lib.h"
namespace softrd {

struct Camera {
	vec3 position;
	vec3 look_at;
	vec3 up;
	float fov; //degree in y direction
	float aspect;
	float near, far;
	mat4 view;
	mat4 projection;

	Camera(const float aspect) {
		position = vec3(0.0, 0.0, 2.0);
		look_at = vec3(0.0, 0.0, -1.0);
		up = vec3(0.0, 1.0, 0.0);
		fov = 120.0; 
		this->aspect = aspect;
		near = 1.0f;
		far = 500.0f;
		UpdateMatrix();
	}

	void UpdateMatrix() {
		//view matrix setting
		vec3 row_z = (look_at - position).normalize();
		vec3 row_y = (up - row_z * (up * row_z)).normalize();
		vec3 row_x = row_y % row_z;
		view = {
			row_x.x, row_x.y, row_x.z, -(row_x * position),
			row_y.x, row_y.y, row_y.z, -(row_y * position),
			row_z.x, row_z.y, row_z.z, -(row_z * position),
			0.0,     0.0,     0.0,     1.0
		};

		//projection matrix setting
		projection.identify();
		float cot_theta = 1.0 / tanf(DegreeToRadian(fov / 2.0));
		projection[0][0] = cot_theta / aspect;
		projection[1][1] = cot_theta;
		projection[2][2] = (far + near) / (near - far);
		projection[2][3] = (2.0 * far * near) / (near - far);
		projection[3][2] = -1.0;


	}

};


} // namespace softrd



#endif // SOFTRD_CAMERA_H_