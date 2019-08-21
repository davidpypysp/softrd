#ifndef SOFTRD_TEXTURE_H_
#define SOFTRD_TEXTURE_H_

#include "src/math/math_lib.h"
#include <SOIL/SOIL.h>

namespace softrd {


//  texture coordinate sample
//  (0.0, 0.0); // left, up
//	(0.0, 1.0); // left, down
//	(1.0, 0.0); // right, up
//	(1.0, 1.0); // right, down

struct Texture {
	int width, height;
	vec3 *pixels;


	Texture(const char* file_name) {
		unsigned char *image = SOIL_load_image(file_name, &width, &height, 0, SOIL_LOAD_RGB);
		if (image == nullptr) return;
		pixels = new vec3[width * height];
		float k = 1.0 / 255.0;
		for (int i = 0; i < width * height; i++) {
			pixels[i].x = image[i * 3] * k;
			pixels[i].y = image[i * 3 + 1] * k;
			pixels[i].z = image[i * 3 + 2] * k;
		}
		SOIL_free_image_data(image);
	}

	~Texture() {
		delete[] pixels;
	}

	vec3 GetColor(const float u, const float v) {
		// bounds-test u,v to make sure nothing will overflow image array bounds 
		float x = Clamp(u, 0.0, 1.0) * (width - 1);
		float y = Clamp(v, 0.0, 1.0) * (height - 1);

		// determine texture cell corner values and perform bilinear interpolation 
		int left = floor(x), right = ceil(x), up = floor(y), down = floor(y);
		vec3 &lu = pixels[ArrayIndex(left, up, width)];
		vec3 &ru = pixels[ArrayIndex(right, up, width)];
		vec3 &rd = pixels[ArrayIndex(right, down, width)];
		vec3 &ld = pixels[ArrayIndex(left, down, width)];

		float kx = x - left, ky = y - up;
		vec3 color = rd * kx * ky + ld * (1 - kx) * ky + ru * kx * (1 - ky) + lu * (1 - kx) * (1 - ky);
		return color;
	}

	vec3 GetColor(const vec2 &uv) {
		return GetColor(uv.x, uv.y);
	}

};

} // namespace softrd

#endif // SOFTRD_TEXTURE_H_