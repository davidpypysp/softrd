#ifndef SOFTRD_RASTERIZER_H_
#define SOFTRD_RASTERIZER_H_

#include <vector>

#include "math/math_lib.h"
#include "primitive_assembly.h"
#include "fragment.h"
#include "camera.h"

namespace softrd {

class Rasterizer {
public:
	enum DrawMode {
		DRAW_LINE,
		DRAW_TRIANGLE
	};
	enum DrawTriangleMode {
		TRIANGLE_FILL,
		TRIANGLE_LINE
	};


	Rasterizer(const int width, const int height, std::vector<Fragment> &fragment_buffer);
	void SetCamera(Camera *camera);

	void DrawLinePrimitive(const LinePrimitive &line);
	// draw triangle on window space by scan-line algorithm
	void DrawTrianglePrimitive(const TrianglePrimitive &triangle, DrawTriangleMode mode);
private:
	void DrawTriangleScanLine(const TrianglePrimitive &triangle);
	void DrawFlatBottomTriangle(const vec3 &bottom_position1, const vec3 &bottom_position2, const vec3 &top_position);
	void DrawFlatTopTriangle(const vec3 &bottom_position, const vec3 &top_position1, const vec3 &top_position2, bool draw_top_integer_line);
	void DrawScanLine(const float x1, const float x2, const float y);
	void LineGenerateFragment(const float x, const float y);
	void TriangleGenerateFragment(const float x, const float y);
	void DrawLine(const vec2 &position1, const vec2 &position2);
	void InitTriangleInterpolation(const TrianglePrimitive &triangle);
	void InitLineInterpolation(const LinePrimitive &line);

	int width_, height_;
	std::vector<Fragment> &fragment_buffer_;
	Camera *camera_;

	DrawMode draw_mode_;
	LinePrimitive line_;
	TrianglePrimitive triangle_; // for triangle interpolation
	vec2 positions_[3]; // for interpolation 
	float perspective_k_; // for perspective texture mapping
	vec2 wrapped_uvs[3];


};


} // namespace softrd

#endif // SOFTRD_RASTERIZER_H_