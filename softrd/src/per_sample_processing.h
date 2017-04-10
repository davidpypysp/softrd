#ifndef SOFTRD_PER_SAMPLE_PROCCESSING_H_
#define SOFTRD_PER_SAMPLE_PROCCESSING_H_

#include "fragment_shader.h"

namespace softrd {

class PerSampleProcessor {
public:
	PerSampleProcessor();

	bool Run();

	FragmentShaderOut in_;
private:

	bool DepthTest();

};

} // namespace softrd

#endif // SOFTRD_PER_SAMPLE_PROCCESSING_H_
