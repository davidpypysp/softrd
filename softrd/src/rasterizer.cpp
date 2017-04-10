#include "rasterizer.h"

namespace softrd {
Rasterizer::Rasterizer(const int width, const int height) : width_(width), height_(height) {
}

void Rasterizer::DrawTriangle(const TrianglePrimitive &triangle, std::vector<Fragment> *fragment_buffer) { // scan line algorithm
    triangle_ = triangle;
    fragment_buffer->clear();
    fragment_buffer_ = fragment_buffer;

    // sorted 3 vertices
    int min_index = 0, max_index = 0;
    for (int i = 1; i < 3; i++) { // find the index of max-y's position and min-y's position
        if ( (triangle.vertex[i].window_position.y < triangle.vertex[min_index].window_position.y) ||
             (triangle.vertex[i].window_position.y == triangle.vertex[min_index].window_position.y && triangle.vertex[i].window_position.x < triangle.vertex[min_index].window_position.x))
            min_index = i;
        if (triangle.vertex[i].window_position.y > triangle.vertex[max_index].window_position.y ||
            (triangle.vertex[i].window_position.y == triangle.vertex[max_index].window_position.y && triangle.vertex[i].window_position.x > triangle.vertex[max_index].window_position.x))
            max_index = i;
    }

    const vec3 &bottom_position = triangle.vertex[min_index].window_position;
    const vec3 &middle_position = triangle.vertex[3 - max_index - min_index].window_position;
    const vec3 &top_position = triangle.vertex[max_index].window_position;

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
	if (x <= 0 || x >= width_ || y < 0 || y >= height_) return;
	cnt++;

    // interpolation process
    vec2 pos0(triangle_.vertex[0].window_position.x, triangle_.vertex[0].window_position.y);
    vec2 pos1(triangle_.vertex[1].window_position.x, triangle_.vertex[1].window_position.y);
    vec2 pos2(triangle_.vertex[2].window_position.x, triangle_.vertex[2].window_position.y);
    vec3 k = GetBarycentricCoordinates(pos0, pos1, pos2, vec2(x, y));
    float z = TriangleInterpolation(triangle_.vertex[0].window_position.z, triangle_.vertex[1].window_position.z, triangle_.vertex[2].window_position.z, k);

    Fragment fragment;
    fragment.window_position = vec3(x, y, z);
    fragment_buffer_->push_back(fragment);


}

vec3 GetBarycentricCoordinates(const vec2 &a, const vec2 &b, const vec2 &c, const vec2 &p) {
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

    float ka = det_pbc / det_abc;
    float kb = det_pca / det_abc;
    float kc = det_pab / det_abc;
    return vec3(ka, kb, kc);
}

template<typename T> T TriangleInterpolation(const T &a, const T &b, const T &c, const vec3 &k) { // T could be float, vec3, vec4, mat3, mat4 ...
    return k.x * a + k.y * b + k.z * c;
}


} // namespace softrd



