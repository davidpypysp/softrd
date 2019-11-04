#ifndef SOFTRD_RENDERING_PIPELINE_H_
#define SOFTRD_RENDERING_PIPELINE_H_

#include <vector>

#include "src/components/camera.h"
#include "src/components/model.h"
#include "src/modules/fragment_shader.h"
#include "src/modules/per_sample_processing.h"
#include "src/modules/rasterizer.h"
#include "src/modules/vertex_loader.h"
#include "src/modules/vertex_shader.h"
#include "src/utils/util.h"

namespace softrd {

class RenderingPipeline {
 public:
  enum DrawMode { DRAW_LINE, DRAW_TRIANGLE };

  const Camera &camera() const { return camera_; }

  RenderingPipeline(const int width, const int height);
  void DrawMesh(
      Mesh &mesh, VertexShader &vertex_shader, FragmentShader &fragment_shader,
      const Rasterizer::DrawTriangleMode tri_mode = Rasterizer::TRIANGLE_LINE,
      const DrawMode draw_mode = DRAW_TRIANGLE);
  void SetShader(VertexShader *vertex_shader, FragmentShader *fragment_shader);
  void Run(const DrawMode mode);  // draw one frame
  void SetPolygonMode(const Rasterizer::DrawTriangleMode mode);
  void ResetBuffer();
  void Clear();
  ~RenderingPipeline();

 private:
  void SetPixel(const int x, const int y, const vec4 &color);
  void SetDepth(const int x, const int y, const float z);
  void SetFrame();
  void DrawFrame();

  unsigned int width_, height_, screen_size_;

  // pipeline stages
  VertexShader *vertex_shader_;
  FragmentShader *fragment_shader_;

  PrimitiveAssembler primitve_assembler_;
  Rasterizer rasterizer_;
  PerSampleProcessor per_sample_proccessor_;

  Camera camera_;

  // all buffers
  std::vector<Vertex> vertex_buffer_;
  std::vector<uint32_t> element_buffer_;
  std::vector<VertexOut> vertex_out_buffer_;
  std::vector<Fragment> fragment_buffer_;
  util::Array<unsigned char> frame_buffer_;
  util::Array<float> depth_buffer_;

  Rasterizer::DrawTriangleMode polygon_mode_;
};

}  // namespace softrd

#endif  // SOFTRD_RENDERING_PIPELINE_H_