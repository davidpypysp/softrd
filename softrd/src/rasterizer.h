#ifndef SOFTRD_RASTERIZER_H_
#define SOFTRD_RASTERIZER_H_

#include <vector>

#include "primitive_assembly.h"
#include "fragment.h"

namespace softrd {

class Rasterizer {
public:
	Rasterizer(const int width, const int height);

	// draw triangle on window space by scan-line algorithm
	void DrawTriangle(const TrianglePrimitive &triangle, std::vector<Fragment> *fragment_buffer);
private:
	void DrawFlatBottomTriangle(const vec3 &bottom_position1, const vec3 &bottom_position2, const vec3 &top_position);
	void DrawFlatTopTriangle(const vec3 &bottom_position, const vec3 &top_position1, const vec3 &top_position2, bool draw_top_integer_line);
	void DrawScanLine(const float x1, const float x2, const float y);
	void GenerateFragment(const float x, const float y);

	int width_, height_;
	TrianglePrimitive triangle_;
	std::vector<Fragment> *fragment_buffer_;

};


vec3 GetBarycentricCoordinates(const vec2 &a, const vec2 &b, const vec2 &c, const vec2 &p);
template<typename T> T TriangleInterpolation(const T &a, const T &b, const T &c, const vec3 &k);



} // namespace softrd

#endif // SOFTRD_RASTERIZER_H_