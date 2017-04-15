#ifndef SOFTRD_CAMERA_H_
#define SOFTRD_CAMERA_H_

#include "math/math_lib.h"
namespace softrd {

struct Camera {
	vec3 position;
	vec3 direction;
	vec3 up;
	vec3 right;
	vec3 world_up;
	float pitch;
	float yaw;
	float fov; //degree in y direction
	float aspect;
	float near, far;
	mat4 view;
	mat4 projection;

	Camera(const float aspect) {
		position = vec3(0.0, 0.0, 2.0);
		direction = vec3(0.0, 0.0, 1.0);
		up = vec3(0.0, 1.0, 0.0);
		right = vec3(1.0, 0.0, 0.0);
		world_up = vec3(0.0, 1.0, 0.0);
		pitch = 0.0;
		yaw = 90.0;

		fov = 120.0; 
		this->aspect = aspect;
		near = 1.0f;
		far = 500.0f;
		SetViewMatrix();
		SetProjectionMatrix();
	}

	void SetViewMatrix() {
		vec3 right = up % direction;
		view = {
			right.x, right.y, right.z, -(right * position),
			up.x, up.y, up.z, -(up * position),
			direction.x, direction.y, direction.z, -(direction * position),
			0.0,     0.0,     0.0,     1.0
		};
	}

	void SetProjectionMatrix() {
		projection.identify();
		float cot_theta = 1.0 / tanf(Radians(fov / 2.0));
		projection[0][0] = cot_theta / aspect;
		projection[1][1] = cot_theta;
		projection[2][2] = (far + near) / (near - far);
		projection[2][3] = (2.0 * far * near) / (near - far);
		projection[3][2] = -1.0;
	}

	void Move(const vec3 &move) {
		position = position + move;
		printf("position: %f, %f, %f\n", position.x, position.y, position.z);
		SetViewMatrix();
	}

	void Rotate(const vec3 &rotate) { // x: pitch, y: yaw, z: roll(not use)
		pitch += rotate.x;
		yaw += rotate.y;
		if (pitch > 89.0) pitch = 89.0;
		else if (pitch < -89.0) pitch = -89.0;
		//if (yaw > 89.0) yaw = 89.0;
		//else if (yaw < -89.0) yaw = -89.0;


		direction.x = cos(Radians(pitch)) * cos(Radians(yaw));
		direction.y = sin(Radians(pitch));
		direction.z = cos(Radians(pitch)) * sin(Radians(yaw));
		direction.normalize();
		right = (world_up % direction).normalize();
		up = direction % right;
		SetViewMatrix();
	}


};


} // namespace softrd



#endif // SOFTRD_CAMERA_H_