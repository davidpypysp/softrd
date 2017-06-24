#ifndef SOFTRD_CLIPPING_H_
#define SOFTRD_CLIPPING_H_

#include "primitive.h"
#include "math/math_lib.h"

#define W_ZERO 0.001 // for negative w clipping

// for Cohen-Sutherland algorithm
#define BL 1
#define BR 2
#define BD 4
#define BT 8
#define BN 16
#define BF 32

namespace softrd {
	bool ClipLineNegativeW(LinePrimitive *line) { // false if need to discard this line
		int negative_num = 0;
		int index = 0;
		for (int i = 0; i < 2; i++) {
			if (line->v[i].position.w < W_ZERO) {
				index = i;
				negative_num++;
			}
		}

		if (negative_num == 0) return true;
		if (negative_num == 2) return false;

		float k = LinearInterpolationCoef(line->v[0].position.w, line->v[1].position.w, W_ZERO);
		vec4 position = LinearInterpolation(line->v[0].position, line->v[1].position, k);
		line->v[index].position = position;
		return true;

	}

	int RegionCode(const vec4 &position) { // Cohen-Sutherland algorithm
		int code = 0;
		if (position.x < -position.w) code |= BL;
		else if (position.x > position.w) code |= BR;
		if (position.y < -position.w) code |= BD;
		else if (position.y > position.w) code |= BT;
		if (position.z < -position.w) code |= BN;
		else if (position.z > position.w) code |= BF;
		return code;
	}

	bool CalcIntersection(const int code, const vec4 &p1, const vec4 &p2, vec4 *result) {
		float a = 0.0;
		vec4 p;
		if (code & BL) {
			a = (p1.w + p1.x) / ((p1.w + p1.x) - (p2.w + p2.x));
			p = (1.0 - a) * p1 + a * p2;
			if (p.y >= -p.w && p.y <= p.w && p.z >= -p.w && p.z <= p.w) {
				*result = p;
				return true;
			}
		}
		else if (code & BR) {
			a = (p1.w - p1.x) / ((p1.w - p1.x) - (p2.w - p2.x));
			p = (1.0 - a) * p1 + a * p2;
			if (p.y >= -p.w && p.y <= p.w && p.z >= -p.w && p.z <= p.w) {
				*result = p;
				return true;
			}
		}

		if(code & BD) {
			a = (p1.w + p1.y) / ((p1.w + p1.y) - (p2.w + p2.y));
			p = (1.0 - a) * p1 + a * p2;
			if (p.x >= -p.w && p.x <= p.w && p.z >= -p.w && p.z <= p.w) {
				*result = p;
				return true;
			}
		}
		else if (code & BT) {
			a = (p1.w - p1.y) / ((p1.w - p1.y) - (p2.w - p2.y));
			p = (1.0 - a) * p1 + a * p2;
			if (p.x >= -p.w && p.x <= p.w && p.z >= -p.w && p.z <= p.w) {
				*result = p;
				return true;
			}
		}

		if (code & BN) {
			a = (p1.w + p1.z) / ((p1.w + p1.z) - (p2.w + p2.z));
			p = (1.0 - a) * p1 + a * p2;
			if (p.x >= -p.w && p.x <= p.w && p.y >= -p.w && p.y <= p.w) {
				*result = p;
				return true;
			}
		}
		else if (code & BF) {
			a = (p1.w - p1.z) / ((p1.w - p1.z) - (p2.w - p2.z));
			p = (1.0 - a) * p1 + a * p2;
			if (p.x >= -p.w && p.x <= p.w && p.y >= -p.w && p.y <= p.w) {
				*result = p;
				return true;
			}
		}
		return false;
	}

	bool ClipLine(LinePrimitive *line) {
		int codes[2];
		vec4 positions[2];
		for (int i = 0; i < 2; ++i) {
			positions[i] = line->v[i].position;
			codes[i] = RegionCode(positions[i]);
		}

		if (codes[0] == 0 && codes[1] == 0) return true; // both in view frustum. No need to clip
		if (codes[0] & codes[1]) return false; // both outside and not get through view frustum. Discard.

		for (int i = 0; i < 2; ++i) {
			vec4 clip_position;
			if (codes[i] != 0) {
				if (CalcIntersection(codes[i], positions[0], positions[1], &clip_position) == false) return false;
				line->v[i].position = clip_position;
			}
		}
		return true;

	}
}

#endif // SOFTRD_CLIPPING_H_