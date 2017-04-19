#ifndef SOFTRD_PER_SAMPLE_PROCCESSING_H_
#define SOFTRD_PER_SAMPLE_PROCCESSING_H_

#include "fragment_shader.h"

namespace softrd {

class PerSampleProcessor {
public:
	PerSampleProcessor(const int width, const int height);
	void Setup(float *depth_buffer);
	bool Run(const FragmentOut &in);

private:

	bool DepthTest(const vec3 &position);
	int width_, height_;
	float *depth_buffer_;

};

} // namespace softrd

#endif // SOFTRD_PER_SAMPLE_PROCCESSING_H_
