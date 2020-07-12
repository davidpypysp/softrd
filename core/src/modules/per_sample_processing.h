#ifndef SOFTRD_PER_SAMPLE_PROCCESSING_H_
#define SOFTRD_PER_SAMPLE_PROCCESSING_H_

#include "src/modules/fragment_shader.h"
#include "src/utils/util.h"

namespace softrd {

class PerSampleProcessor {
 public:
  PerSampleProcessor(const int width, const int height,
                     std::vector<float> &depth_buffer);
  bool Run(const FragmentOut &in);

 private:
  bool DepthTest(const math::vec3 &position);
  int width_, height_;
  std::vector<float> &depth_buffer_;
};

}  // namespace softrd

#endif  // SOFTRD_PER_SAMPLE_PROCCESSING_H_
