#ifndef SOFTRD_PER_SAMPLE_PROCCESSING_H_
#define SOFTRD_PER_SAMPLE_PROCCESSING_H_

#include "fragment_shader.h"
#include "util.h"

namespace softrd {

class PerSampleProcessor {
public:
	PerSampleProcessor(const int width, const int height, util::Array<float> &depth_buffer);
	void Setup(util::Array<float> &depth_buffer);
	bool Run(const FragmentOut &in);

private:

	bool DepthTest(const vec3 &position);
	int width_, height_;
	util::Array<float> &depth_buffer_;

};

} // namespace softrd

#endif // SOFTRD_PER_SAMPLE_PROCCESSING_H_
