#ifndef SOFTRD_RENDERING_PIPELINE_H_
#define SOFTRD_RENDERING_PIPELINE_H_

#include <memory>
#include <vector>

#include "src/components/camera.h"
#include "src/components/model.h"
#include "src/modules/fragment_shader.h"
#include "src/modules/per_sample_processing.h"
#include "src/modules/rasterizer.h"
#include "src/modules/vertex_loader.h"
#include "src/modules/vertex_shader.h"
#include "src/renderer/scene_object.h"
#include "src/utils/util.h"

namespace softrd {

class RenderingPipeline {
 public:
  enum DrawMode { DRAW_LINE, DRAW_TRIANGLE };

  RenderingPipeline();

  void Reset(const int width, const int height, std::shared_ptr<Camera> camera);
  void DrawSceneObject(const std::shared_ptr<SceneObject> &scene_object);
  void DrawMesh(
      Mesh &mesh, VertexShader &vertex_shader, FragmentShader &fragment_shader,
      const Rasterizer::DrawTriangleMode tri_mode = Rasterizer::TRIANGLE_LINE,
      const DrawMode draw_mode = DRAW_TRIANGLE);
  void SetShader(VertexShader *vertex_shader, FragmentShader *fragment_shader);
  void Run(const DrawMode mode);  // draw one frame
  void SetPolygonMode(const Rasterizer::DrawTriangleMode mode);
  void SetWindowFrameBuffer(uint8_t *buffer);
  void ResetBuffer();
  void Clear();
  ~RenderingPipeline();

  void set_camera(const std::shared_ptr<Camera> &camera) { camera_ = camera; }
  std::shared_ptr<Camera> camera() const { return camera_; }

 private:
  void SetPixel(const int x, const int y, const math::vec4 &color);
  void SetPixelToWindow(const int x, const int y, const math::vec4 &color);
  void SetDepth(const int x, const int y, const float z);
  void SetFrame();
  void DrawFrame();

  unsigned int width_, height_, screen_size_;

  // pipeline stages
  VertexShader *vertex_shader_;
  FragmentShader *fragment_shader_;

  std::unique_ptr<PrimitiveAssembler> primitive_assembler_;
  std::unique_ptr<Rasterizer> rasterizer_;
  std::unique_ptr<PerSampleProcessor> per_sample_processor_;

  std::shared_ptr<Camera> camera_ = nullptr;

  // all buffers
  std::vector<Vertex> vertex_buffer_;
  std::vector<uint32_t> element_buffer_;
  std::vector<VertexOut> vertex_out_buffer_;
  std::vector<Fragment> fragment_buffer_;
  util::Array<unsigned char> frame_buffer_;
  util::Array<float> depth_buffer_;
  uint8_t *window_frame_buffer_;

  Rasterizer::DrawTriangleMode polygon_mode_;
};

}  // namespace softrd

#endif  // SOFTRD_RENDERING_PIPELINE_H_