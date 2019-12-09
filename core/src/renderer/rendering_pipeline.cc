#include "src/renderer/rendering_pipeline.h"

namespace softrd {

// Renderer initialization, include each stage's initialization
RenderingPipeline::RenderingPipeline(const int width, const int height)
    : width_(width),
      height_(height),
      screen_size_(width * height),
      frame_buffer_(screen_size_ * 4),
      depth_buffer_(screen_size_),
      primitve_assembler_(width, height, vertex_out_buffer_),
      rasterizer_(width, height, fragment_buffer_),
      per_sample_proccessor_(width, height, depth_buffer_),
      camera_((float)width / (float)height),
      polygon_mode_(Rasterizer::TRIANGLE_FILL) {
  std::cout << "rendering pipeline constructor()" << std::endl;
  rasterizer_.SetCamera(&camera_);
  // DrawObject(spot_light_lamp, vertex_shader_light, fragment_shader);
}

// Draw mesh using rendering pipeline
void RenderingPipeline::DrawMesh(Mesh &mesh, VertexShader &vertex_shader,
                                 FragmentShader &fragment_shader,
                                 const Rasterizer::DrawTriangleMode tri_mode,
                                 const DrawMode draw_mode) {
  mesh.LoadBuffer(vertex_buffer_, element_buffer_);
  SetShader(&vertex_shader, &fragment_shader);
  SetPolygonMode(tri_mode);
  Run(draw_mode);
}

// use appointed vertex shader and fragment shader for rendering
void RenderingPipeline::SetShader(VertexShader *vertex_shader,
                                  FragmentShader *fragment_shader) {
  vertex_shader_ = vertex_shader;
  fragment_shader_ = fragment_shader;
}

// rendering pipeline program
void RenderingPipeline::Run(const DrawMode mode) {
  // vertex shader stage
  vertex_out_buffer_.clear();
  VertexOut vertex_out;
  for (int i = 0; i < vertex_buffer_.size(); i++) {
    vertex_shader_->Run(vertex_buffer_[i], &vertex_out);
    vertex_out_buffer_.push_back(vertex_out);
  }

  primitve_assembler_.Reset();
  if (mode == DRAW_LINE) {
    for (int index = 0; index < element_buffer_.size() / 2; ++index) {
      LinePrimitive line;
      // primitive assemble stage
      if (primitve_assembler_.AssembleLine(element_buffer_[index * 2],
                                           element_buffer_[index * 2 + 1],
                                           &line) == false)
        continue;

      // rasterize stage
      rasterizer_.DrawLinePrimitive(line);

      // fragment shader stage
      FragmentOut fragment_shader_out;
      for (Fragment &fragment : fragment_buffer_) {
        fragment_shader_->Run(fragment, &fragment_shader_out);
        if (per_sample_proccessor_.Run(fragment_shader_out) == true) {
          // test fragment success, pass into framebuffer;
          SetPixel(fragment_shader_out.window_position.x,
                   fragment_shader_out.window_position.y,
                   fragment_shader_out.color);
          SetDepth(fragment_shader_out.window_position.x,
                   fragment_shader_out.window_position.y,
                   fragment_shader_out.window_position.z);
        }
      }
    }
  } else if (mode == DRAW_TRIANGLE) {
    for (int index = 0; index < element_buffer_.size() / 3; ++index) {
      std::cout << "index " << index << std::endl;

      std::vector<TrianglePrimitive> triangles;
      primitve_assembler_.AssembleTriangle(
          element_buffer_[index * 3], element_buffer_[index * 3 + 1],
          element_buffer_[index * 3 + 2], &triangles);
      std::cout << triangles.size() << std::endl;
      for (TrianglePrimitive &triangle : triangles) {
        std::cout << "triangle " << std::endl;

        rasterizer_.DrawTrianglePrimitive(triangle, polygon_mode_);

        FragmentOut fragment_shader_out;
        for (Fragment &fragment : fragment_buffer_) {
          fragment_shader_->Run(fragment, &fragment_shader_out);
          if (per_sample_proccessor_.Run(fragment_shader_out) == true) {
            // test fragment success, pass into framebuffer;
            SetPixel(fragment_shader_out.window_position.x,
                     fragment_shader_out.window_position.y,
                     fragment_shader_out.color);
            SetDepth(fragment_shader_out.window_position.x,
                     fragment_shader_out.window_position.y,
                     fragment_shader_out.window_position.z);
          }
        }
      }
    }
  }
}

// set polygonmode in triangle mode or wireframe mode
void RenderingPipeline::SetPolygonMode(
    const Rasterizer::DrawTriangleMode mode) {
  polygon_mode_ = mode;
}

void RenderingPipeline::ResetBuffer() {
  frame_buffer_.Fill(10);
  depth_buffer_.Fill(1.0);
}

RenderingPipeline::~RenderingPipeline() {}

// set pixel to the appointed color
void RenderingPipeline::SetPixel(const int x, const int y, const vec4 &color) {
  if (0 <= x && x <= width_ && 0 <= y && y <= height_) {
    int offset = (y * width_ + x) * 4;
    std::cout << "offset" << offset << std::endl;
    frame_buffer_[offset] = Clamp(color.z * 255, 0, 255);      // b
    frame_buffer_[offset + 1] = Clamp(color.y * 255, 0, 255);  // g
    frame_buffer_[offset + 2] = Clamp(color.x * 255, 0, 255);  // r
    frame_buffer_[offset + 3] = Clamp(color.w * 255, 0, 255);  // a
  }
}

// set depth buffer value
void RenderingPipeline::SetDepth(const int x, const int y, const float z) {
  depth_buffer_[y * width_ + x] = z;
}

}  // namespace softrd
