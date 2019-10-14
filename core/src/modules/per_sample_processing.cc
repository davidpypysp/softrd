#include "per_sample_processing.h"

namespace softrd {

PerSampleProcessor::PerSampleProcessor(const int width, const int height, util::Array<float> &depth_buffer) :
width_(width),
height_(height),
depth_buffer_(depth_buffer) {
}

void PerSampleProcessor::Setup(util::Array<float> &depth_buffer) {
	depth_buffer_ = depth_buffer;
}

bool PerSampleProcessor::Run(const FragmentOut &in) {
	if (!DepthTest(in.window_position)) return false;
	return true;
}

bool PerSampleProcessor::DepthTest(const vec3 &position) {
	int index = (int)position.y * width_ + (int)position.x;
	return position.z < depth_buffer_[index];
}

} // namespace softrd


