#include "rasterizer.h"

namespace softrd {
Rasterizer::Rasterizer(const int width, const int height) : width_(width), height_(height) {
}

void Rasterizer::DrawTriangle(const TrianglePrimitive &triangle, std::vector<Fragment> *fragment_buffer, DrawTriangleMode mode) { // scan line algorithm
    fragment_buffer->clear();
    fragment_buffer_ = fragment_buffer;

	if (mode == TRIANGLE_FILL) {
		DrawTriangleScanLine(triangle);
	}
	else if (mode == TRIANGLE_LINE) {
		vec2 position0(triangle.vertex[0].position.x, triangle.vertex[0].position.y);
		vec2 position1(triangle.vertex[1].position.x, triangle.vertex[1].position.y);
		vec2 position2(triangle.vertex[2].position.x, triangle.vertex[2].position.y);
		DrawLine(position0, position1);
		DrawLine(position1, position2);
		DrawLine(position2, position0);
	}


}

void Rasterizer::DrawTriangleScanLine(const TrianglePrimitive &triangle) {
	triangle_ = triangle;

	// sorted 3 vertices
	int min_index = 0, max_index = 0;
	for (int i = 1; i < 3; i++) { // find the index of max-y's position and min-y's position
		if ((triangle.vertex[i].position.y < triangle.vertex[min_index].position.y) ||
			(triangle.vertex[i].position.y == triangle.vertex[min_index].position.y && triangle.vertex[i].position.x < triangle.vertex[min_index].position.x))
			min_index = i;
		if (triangle.vertex[i].position.y > triangle.vertex[max_index].position.y ||
			(triangle.vertex[i].position.y == triangle.vertex[max_index].position.y && triangle.vertex[i].position.x > triangle.vertex[max_index].position.x))
			max_index = i;
	}

	vec3 bottom_position(triangle.vertex[min_index].position.x, triangle.vertex[min_index].position.y, triangle.vertex[min_index].position.z);
	vec3 middle_position(triangle.vertex[3 - max_index - min_index].position.x, triangle.vertex[3 - max_index - min_index].position.y, triangle.vertex[3 - max_index - min_index].position.z);
	vec3 top_position(triangle.vertex[max_index].position.x, triangle.vertex[max_index].position.y, triangle.vertex[max_index].position.z);

	if (bottom_position.y == top_position.y) { // 3 positions in same line
		if (top_position.y == floorf(top_position.y)) DrawScanLine(bottom_position.x, top_position.x, top_position.y);
	}
	else if (bottom_position.y == middle_position.y) { // it is flat bottom triangle
		DrawFlatBottomTriangle(bottom_position, middle_position, top_position);
	}
	else if (middle_position.y == top_position.y) { // it is flat top triangle
		DrawFlatTopTriangle(bottom_position, middle_position, top_position, true);
	}
	else { // seperate into flat bottom triangle and flat top triangle
		float middle_x2 = top_position.x - (top_position.y - middle_position.y) * (top_position.x - bottom_position.x) / (top_position.y - bottom_position.y);
		vec3 middle_position2(middle_x2, middle_position.y, 0.0); // z value doesn't matter for now
		if (middle_position.x < middle_position2.x) {
			DrawFlatBottomTriangle(middle_position, middle_position2, top_position);
			DrawFlatTopTriangle(bottom_position, middle_position, middle_position2, false);
		}
		else {
			DrawFlatBottomTriangle(middle_position2, middle_position, top_position);
			DrawFlatTopTriangle(bottom_position, middle_position2, middle_position, false);
		}
	}

}

void Rasterizer::DrawFlatBottomTriangle(const vec3 &bottom_position1, const vec3 &bottom_position2, const vec3 &top_position) {
    float x_slope1 = (top_position.x - bottom_position1.x) / (top_position.y - bottom_position1.y);
    float x_slope2 = (top_position.x - bottom_position2.x) / (top_position.y - bottom_position2.y);
    float start_y = ceilf(bottom_position1.y);
    float x1 = bottom_position1.x + x_slope1 * (start_y - bottom_position1.y);
    float x2 = bottom_position2.x + x_slope2 * (start_y - bottom_position1.y);
    for (float y = start_y; y <= top_position.y; ++y) {
        DrawScanLine(x1, x2, y);
        x1 += x_slope1;
        x2 += x_slope2;
    }
}

void Rasterizer::DrawFlatTopTriangle(const vec3 &bottom_position, const vec3 &top_position1, const vec3 &top_position2, bool draw_top_integer_line) {
    float x_slope1 = (top_position1.x - bottom_position.x) / (top_position1.y - bottom_position.y);
    float x_slope2 = (top_position2.x - bottom_position.x) / (top_position2.y - bottom_position.y);
    float start_y = ceilf(bottom_position.y);
    float x1 = bottom_position.x + x_slope1 * (start_y - bottom_position.y);
    float x2 = bottom_position.x + x_slope2 * (start_y - bottom_position.y);
    for (float y = start_y; y < top_position1.y; ++y) {
        DrawScanLine(x1, x2, y);
        x1 += x_slope1;
        x2 += x_slope2;
    }
    if (draw_top_integer_line && top_position1.y == floorf(top_position1.y)) { // for special case
        DrawScanLine(x1, x2, top_position1.y);
    }
}

void Rasterizer::DrawScanLine(const float x1, const float x2, const float y) {
    for (float x = ceilf(x1); x <= x2; ++x) {
        GenerateFragment(x, y);
    }
}

void Rasterizer::GenerateFragment(const float x, const float y) {
    if (x < 0 || x >= width_ || y < 0 || y >= height_) return;

    // interpolation process
    vec2 pos0(triangle_.vertex[0].position.x, triangle_.vertex[0].position.y);
    vec2 pos1(triangle_.vertex[1].position.x, triangle_.vertex[1].position.y);
    vec2 pos2(triangle_.vertex[2].position.x, triangle_.vertex[2].position.y);
    vec3 k = GetBarycentricCoordinates(pos0, pos1, pos2, vec2(x, y));
    float z = TriangleInterpolation(triangle_.vertex[0].position.z, triangle_.vertex[1].position.z, triangle_.vertex[2].position.z, k);

    Fragment fragment;
    fragment.window_position = vec3(x, y, z);
    fragment_buffer_->push_back(fragment);


}

void Rasterizer::DrawLine(const vec2 &position1, const vec2 &position2) {
	int x1 = roundf(position1.x), y1 = roundf(position1.y);
	int x2 = roundf(position2.x), y2 = roundf(position2.y);
	bool steep = abs(y1 - y2) > abs(x1 - x2);
	if (steep) {
		Swap(x1, y1);
		Swap(x2, y2);
	}
	if (x1 > x2) {
		Swap(x1, x2);
		Swap(y1, y2);
	}
	int dx = x2 - x1;
	int dy = abs(y2 - y1);
	int error = -dx;
	int delta_error = 2 * dy, reset_error = 2 * dx;
	int y = y1;
	int y_step = y1 < y2 ? 1 : -1;
	for (int x = x1; x <= x2; x++) {
		vec2 position(x, y);
		if (steep) {
			position.x = y;
			position.y = x;
		}
		if (position.x >= 0 && position.x < width_ && position.y >= 0 && position.y < height_) {
			Fragment fragment;
			fragment.window_position = vec3(position.x, position.y, 0);
			fragment_buffer_->push_back(fragment);
		}

		error += delta_error;
		if (error > 0) {
			y += y_step;
			error -= reset_error;
		}
	}
}

vec3 GetBarycentricCoordinates(const vec2 &a, const vec2 &b, const vec2 &c, const vec2 &p) {
	/*
    mat3 m_abc = {
        1, a.x, a.y,
        1, b.x, b.y,
        1, c.x, c.y,
    };
    mat3 m_pbc = {
        1, p.x, p.y,
        1, b.x, b.y,
        1, c.x, c.y,
    };
    mat3 m_pca = {
        1, p.x, p.y,
        1, c.x, c.y,
        1, a.x, a.y,
    };
    mat3 m_pab = {
        1, p.x, p.y,
        1, a.x, a.y,
        1, b.x, b.y,
    };
    float det_abc = m_abc.det();
    float det_pbc = m_pbc.det();
    float det_pca = m_pca.det();
    float det_pab = m_pab.det();
	*/

	float det_abc = b.x * c.y + a.x * b.y + a.y * c.x - b.x * a.y - c.x * b.y - c.y * a.x;
	float det_pbc = b.x * c.y + p.x * b.y + p.y * c.x - b.x * p.y - c.x * b.y - c.y * p.x;
	float det_pca = c.x * a.y + p.x * c.y + p.y * a.x - c.x * p.y - a.x * c.y - a.y * p.x;
	float det_pab = a.x * b.y + p.x * a.y + p.y * b.x - a.x * p.y - b.x * a.y - b.y * p.x;

    return vec3(det_pbc / det_abc, det_pca / det_abc, det_pab / det_abc);
}

template<typename T> T TriangleInterpolation(const T &a, const T &b, const T &c, const vec3 &k) { // T could be float, vec3, vec4, mat3, mat4 ...
    return k.x * a + k.y * b + k.z * c;
}


} // namespace softrd



