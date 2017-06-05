#ifndef SOFTRD_MATH_VECTOR_H_
#define SOFTRD_MATH_VECTOR_H_

#include <math.h>
#include <assert.h>


namespace softrd {

struct vec2 {
	float x, y;

	vec2(const float x = 0.0, const float y = 0.0) : x(x), y(y) {};

	inline vec2 operator + (const vec2 &b) const { return vec2(x + b.x, y + b.y); }
	inline vec2 operator - (const vec2 &b) const { return vec2(x - b.x, y - b.y); }
	inline vec2 operator * (const float b) const { return vec2(x * b, y * b); }
	inline float operator * (const vec2 &b) const { return x*b.x + y*b.y; } // dot product
	inline vec2 operator / (const float b) const { return vec2(x / b, y / b); }
	inline vec2& operator = (const vec2 &b) { x = b.x; y = b.y; return *this; }
	inline vec2 operator - () const { return vec2(-x, -y); }
	inline float length() { return sqrt(x*x + y*y); }
	inline vec2& normalize() { return *this = *this / length(); }
	inline void move(const vec2 &b) { x += b.x; y += b.y; }



	inline float& operator [] (const int index) {
			switch (index) {
			case 0: return x;
			case 1: return y;
			default: assert("vec2 index out of range!");
		}
	}

};

inline vec2 operator * (const float a, const vec2 &b) { return b * a; }



struct vec3 {
	float x, y, z;

	vec3(const float x = 0.0, const float y = 0.0, const float z = 0.0) : x(x), y(y), z(z) {};
	vec3(const vec2 &b, const float z = 0.0) : x(b.x), y(b.y), z(z) {};

	inline vec3 operator + (const vec3 &b) const { return vec3(x + b.x, y + b.y, z + b.z); }
	inline vec3 operator - (const vec3 &b) const { return vec3(x - b.x, y - b.y, z - b.z); }
	inline vec3 operator * (const float b) const { return vec3(x*b, y*b, z*b); }
	inline float operator * (const vec3 &b) const { return x*b.x + y*b.y + z*b.z; } // dot product
	inline vec3 operator % (const vec3 &b) const { return vec3(y*b.z - z*b.y, z*b.x - x*b.z, x*b.y - y*b.x); } // cross product
	inline vec3 operator / (const float b) const { return vec3(x / b, y / b, z / b); }
	inline vec3& operator = (const vec3 &b) { x = b.x; y = b.y; z = b.z; return *this; }
	inline vec3 operator - () const { return vec3(-x, -y, -z); }
	inline float length() { return sqrt(x*x + y*y + z*z); }
	inline vec3& normalize() { return *this = *this / length(); }
	inline vec3 multiply(const vec3 &b) const { return vec3(x*b.x, y*b.y, z*b.z); }
	inline void move(const vec3 &b) { x += b.x; y += b.y; z += b.z; }

	inline float& operator [] (const int index) {
		switch (index) {
			case 0: return x;
			case 1: return y;
			case 2: return z;
			default: assert("vec3 index out of range!");
		}
	}

};

inline vec3 operator * (const float a, const vec3 &b) { return b * a; }


struct vec4 {
	float x, y, z, w;

	vec4(const float x = 0.0, const float y = 0.0, const float z = 0.0, const float w = 0.0) : x(x), y(y), z(z), w(w) {};
	vec4(const vec2 &b, const float z = 0.0, const float w = 0.0) : x(b.x), y(b.y), z(z), w(w) {};
	vec4(const vec3 &b, const float w = 0.0) : x(b.x), y(b.y), z(b.z), w(w) {};



	inline vec4 operator + (const vec4 &b) const { return vec4(x + b.x, y + b.y, z + b.z, w + b.w); }
	inline vec4 operator - (const vec4 &b) const { return vec4(x - b.x, y - b.y, z - b.z, w - b.w); }
	inline vec4 operator * (const float b) const { return vec4(x*b, y*b, z*b, w*b); }
	inline float operator * (const vec4 &b) const { return x*b.x + y*b.y + z*b.z + w*b.w; } // dot product
	inline vec4 operator / (const float b) const { return vec4(x / b, y / b, z / b, w / b); }
	inline vec4& operator = (const vec4 &b) { x = b.x; y = b.y; z = b.z, w = b.w; return *this; }
	inline vec4 operator - () const { return vec4(-x, -y, -z, -w); }
	inline float length() { return sqrt(x*x + y*y + z*z + w*w); }
	inline vec4& normalize() { return *this = *this / length(); }
	inline vec3 homogenize() { return vec3(x / w, y / w, z / w); }
	inline void move(const vec4 &b) { x += b.x; y += b.y; z += b.z; w += b.w; }
	inline vec3 getVec3() { return vec3(x, y, z); }


	inline float& operator [] (const int index) {
		switch (index) {
			case 0: return x;
			case 1: return y;
			case 2: return z;
			case 3: return w;
			default: assert("vec3 index out of range!");
		}
	}

};

inline vec4 operator * (const float a, const vec4 &b) { return b * a; }







} // namespace softrd


#endif // SOFTRD_MATH_VECTOR_H_
