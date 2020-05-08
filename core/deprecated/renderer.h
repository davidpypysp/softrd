#ifndef SOFTRD_RENDERER_H_
#define SOFTRD_RENDERER_H_

#include <chrono>
#include <vector>

#include "src/common/model.h"
#include "src/devices/device.h"
#include "src/inputs/input.h"
#include "src/modules/fragment_shader.h"
#include "src/modules/per_sample_processing.h"
#include "src/modules/rasterizer.h"
#include "src/modules/vertex_loader.h"
#include "src/modules/vertex_shader.h"
#include "src/scene/camera.h"
#include "src/utils/util.h"

using namespace std::chrono;

namespace softrd {

// Renderer class deals with the whole process of rendering pipeline
// It start from reading .obj file to finally set the frame buffer to the screen
class Renderer {
 public:
  enum DrawMode { DRAW_LINE, DRAW_TRIANGLE };

  Renderer(const int width, const int height);
  void RunExample();
  void RunExample2();
  void SetShader(VertexShader *vertex_shader, FragmentShader *fragment_shader);
  void Draw(const DrawMode mode);  // draw one frame
  void DrawObject(
      Mesh &mesh, VertexShader &vertex_shader, FragmentShader &fragment_shader,
      const Rasterizer::DrawTriangleMode tri_mode = Rasterizer::TRIANGLE_LINE,
      const DrawMode draw_mode = DRAW_TRIANGLE);
  void SetPolygonMode(const Rasterizer::DrawTriangleMode mode);
  void ResetBuffer();
  void Clear();
  ~Renderer();

 private:
  void SetPixel(const int x, const int y, const math::vec4 &color);
  void SetDepth(const int x, const int y, const float z);
  void SetFrame();
  void SetUI();
  void DrawFrame();
  void Input();
  bool Press();

  void LoadCoordinateAxis();
  void DrawCoordinateAxis();

  unsigned int width_, height_, screen_size_;

  // frame setting
  time_point<steady_clock> last_time_;
  double delta_time_;
  float fps_;
  unsigned int frame_count_;

  // pipeline stages
  VertexShader *vertex_shader_;
  FragmentShader *fragment_shader_;

  PrimitiveAssembler primitve_assembler_;
  Rasterizer rasterizer_;
  PerSampleProcessor per_sample_proccessor_;
  Device device_;

  scene::Camera camera_;

  // all buffers
  std::vector<Vertex> vertex_buffer_;
  std::vector<uint32_t> element_buffer_;
  std::vector<VertexOut> vertex_out_buffer_;
  std::vector<Fragment> fragment_buffer_;
  util::Array<unsigned char> frame_buffer_;
  util::Array<float> depth_buffer_;

  Rasterizer::DrawTriangleMode polygon_mode_;

  // coordinate axis
  Mesh axis_lines_[3], grid_line_x_, grid_line_y_;

  // input handling
  std::vector<InputUnit *> inputs_;
  float input_index_;
  const float kPressValue = 0.18;
};

}  // namespace softrd

#endif  // SOFTRD_RENDERER_H_