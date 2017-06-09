#ifndef SOFTRD_MATH_MATRIX_H_
#define SOFTRD_MATH_MATRIX_H_

#include <assert.h>
#include <iostream>

#include "vector.h"


namespace softrd {


struct mat3 {
	float value[3][3];

	explicit mat3() { memset(value, 0, sizeof(value)); }

	mat3(const std::initializer_list<float> &list) {
		assert(list.size() == 9);
		int i = 0;
		for (float v : list) {
			this->value[i / 3][i % 3] = v;
			i++;
		}
	}

	mat3(const std::initializer_list<std::initializer_list<float>> &lists) {
		assert(lists.size() == 3);
		int i = 0;
		for (std::initializer_list<float> list : lists) {
			assert(list.size() == 3);
			for (float v : list) {
				this->value[i / 3][i % 3] = v;
				i++;
			}
		}
	}

	inline float* operator [] (const int index) {
		return value[index];
	}

	inline void identify() {
		memset(value, 0, sizeof(value));
		value[0][0] = value[1][1] = value[2][2]  = 1.0;
	}

	inline void clear() {
		memset(value, 0, sizeof(value));
	}

	inline mat3 operator + (const mat3 &b) const {
		mat3 result;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				result.value[i][j] = value[i][j] + b.value[i][j];
		return result;
	}

	inline mat3 operator - (const mat3 &b) const {
		mat3 result;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				result.value[i][j] = value[i][j] - b.value[i][j];
		return result;
	}

	inline mat3 operator * (const mat3 &b) const {
		mat3 result;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				for (int k = 0; k < 3; k++) result.value[i][j] += value[i][k] * b.value[k][j];
			}
		}
		return result;
	}

	inline mat3 operator * (const float k) const {
		mat3 result;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) result.value[i][j] = value[i][j] * k;
		}
		return result;
	}

	inline vec3 operator * (const vec3 &b) const {
		vec3 result(
			value[0][0] * b.x + value[0][1] * b.y + value[0][2] * b.z,
			value[1][0] * b.x + value[1][1] * b.y + value[1][2] * b.z,
			value[2][0] * b.x + value[2][1] * b.y + value[2][2] * b.z
		);
		return result;
	}


	inline mat3 operator / (const float k) const {
		mat3 result;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				result.value[i][j] = value[i][j] / k;
			}
		}
		return result;
	}

	inline mat3& operator += (const mat3 &b) {
		*this = *this + b;
		return *this;
	}

	inline mat3& operator -= (const mat3 &b) {
		*this = *this - b;
		return *this;
	}

	inline mat3& operator *= (const float k) {
		*this = *this * k;
		return *this;
	}

	inline mat3& operator /= (const float k) {
		*this = *this / k;
		return *this;
	}


	inline float det() {
		return value[1][1] * value[2][2] * value[3][3]
			 + value[1][2] * value[2][3] * value[3][1]
			 + value[1][3] * value[2][1] * value[3][2]
			 - value[1][3] * value[2][2] * value[3][1]
			 - value[1][1] * value[2][3] * value[3][2]
			 - value[1][2] * value[2][1] * value[3][3];
	}



};

inline mat3 operator * (const float k, const mat3 &a) { return a * k; }



struct mat4 {
	float value[4][4];

	explicit mat4() { memset(value, 0, sizeof(value)); }

	mat4(const std::initializer_list<float> &list) {
		assert(list.size() == 16);
		int i = 0;
		for (float v : list) {
			this->value[i / 4][i % 4] = v;
			i++;
		}
	}

	mat4(const std::initializer_list<std::initializer_list<float>> &lists) {
		assert(lists.size() == 4);
		int i = 0;
		for (std::initializer_list<float> list : lists) {
			assert(list.size() == 4);
			for (float v : list) {
				this->value[i / 4][i % 4] = v;
				i++;
			}
		}
	}

	inline float* operator [] (const int index) {
		return value[index];
	}

	inline void identify() {
		memset(value, 0, sizeof(value));
		value[0][0] = value[1][1] = value[2][2] = value[3][3] = 1.0;
	}

	inline void clear() {
		memset(value, 0, sizeof(value));
	}

	inline mat4 mat4::operator + (const mat4 &b) const {
		mat4 result;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				result.value[i][j] = value[i][j] + b.value[i][j];
		return result;
	}

	inline mat4 mat4::operator - (const mat4 &b) const {
		mat4 result;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				result.value[i][j] = value[i][j] - b.value[i][j];
		return result;
	}

	inline mat4 mat4::operator * (const mat4 &b) const {
		mat4 result;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				for (int k = 0; k < 4; k++) result.value[i][j] += value[i][k] * b.value[k][j];
			}
		}
		return result;
	}

	inline mat4 mat4::operator * (const float k) const {
		mat4 result;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) result.value[i][j] = value[i][j] * k;
		}
		return result;
	}

	inline vec4 operator * (const vec4 &b) const {
		vec4 result(
			value[0][0] * b.x + value[0][1] * b.y + value[0][2] * b.z + value[0][3] * b.w,
			value[1][0] * b.x + value[1][1] * b.y + value[1][2] * b.z + value[1][3] * b.w,
			value[2][0] * b.x + value[2][1] * b.y + value[2][2] * b.z + value[2][3] * b.w,
			value[3][0] * b.x + value[3][1] * b.y + value[3][2] * b.z + value[3][3] * b.w
		);
		return result;
	}

	inline mat4 operator / (const float k) const {
		mat4 result;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				result.value[i][j] = value[i][j] / k;
			}
		}
		return result;
	}

	inline mat4& operator += (const mat4 &b) {
		*this = *this + b;
		return *this;
	}

	inline mat4& operator -= (const mat4 &b) {
		*this = *this - b;
		return *this;
	}

	inline mat4& operator *= (const float k) {
		*this = *this * k;
		return *this;
	}

	inline mat4& operator /= (const float k) {
		*this = *this / k;
		return *this;
	}

	inline void translate(const float x, const float y, const float z) {
		value[0][3] = x;
		value[1][3] = y;
		value[2][3] = z;
	}

	inline void translate(const vec3 &b) {
		translate(b.x, b.y, b.z);
	}

	inline void scale(const float x, const float y, const float z) {
		value[0][0] = x;
		value[1][1] = y;
		value[2][2] = z;
	}

	inline void scale(const vec3 &b) {
		scale(b.x, b.y, b.z);
	}

	inline void rotateX(const float theta) { // radian
		identify();
		value[1][1] = cos(theta);
		value[1][2] = -sin(theta);
		value[2][1] = sin(theta);
		value[2][2] = cos(theta);
	}

	inline void rotateY(const float theta) { // radian
		identify();
		value[0][0] = cos(theta);
		value[0][2] = sin(theta);
		value[2][0] = -sin(theta);
		value[2][2] = cos(theta);
	}

	inline void rotateZ(const float theta) { // radian
		identify();
		value[0][0] = cos(theta);
		value[0][1] = -sin(theta);
		value[1][0] = sin(theta);
		value[1][1] = cos(theta);
	}


};

inline mat4 operator * (const float k, const mat4 &a) { return a * k; }

}


#endif // SOFTRD_MATH_MATRIX_H_