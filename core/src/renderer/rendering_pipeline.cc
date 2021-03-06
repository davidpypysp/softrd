#include "src/renderer/rendering_pipeline.h"

namespace softrd {

RenderingPipeline::RenderingPipeline() {}

// rendering pipeline initialization, include each stage's initialization
void RenderingPipeline::Reset(const int width, const int height,
                              std::shared_ptr<scene::Camera> camera) {
  width_ = width;
  height_ = height;
  screen_size_ = width * height;

  depth_buffer_.resize(screen_size_ * 4);
  frame_buffer_.resize(screen_size_ * 4);

  ResetBuffer();

  camera_ = camera;

  primitive_assembler_ =
      std::make_unique<PrimitiveAssembler>(width, height, vertex_out_buffer_);

  rasterizer_ = std::make_unique<Rasterizer>(width, height, fragment_buffer_);
  if (camera_) {
    rasterizer_->SetCamera(camera_.get());
  }
  polygon_mode_ = Rasterizer::TRIANGLE_FILL;

  per_sample_processor_ =
      std::make_unique<PerSampleProcessor>(width, height, depth_buffer_);
}

void RenderingPipeline::DrawSceneObject(
    const std::shared_ptr<scene::SceneObject> &scene_object) {
  math::mat4 model_matrix;
  model_matrix.identify();

  model_matrix.translate(scene_object->position());

  // TODO: fix rotation issue
  // model_matrix.rotateX(scene_object->rotation().x);
  // model_matrix.rotateY(scene_object->rotation().y);
  // model_matrix.rotateZ(scene_object->rotation().z);

  model_matrix.scale(scene_object->scale());

  std::shared_ptr<VertexShaderLight> vertex_shader_light =
      std::dynamic_pointer_cast<VertexShaderLight>(
          scene_object->vertex_shader());

  if (!vertex_shader_light) {
    return;
  }

  vertex_shader_light->set_transform(camera_->projection() * camera_->view() *
                                     model_matrix);
  vertex_shader_light->set_model(model_matrix);

  this->DrawMesh(*(scene_object->mesh()), *vertex_shader_light,
                 *(scene_object->fragment_shader()), Rasterizer::TRIANGLE_FILL);
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
    const auto &vertex = vertex_buffer_[i];
  }

  for (int i = 0; i < vertex_buffer_.size(); i++) {
    vertex_shader_->Run(vertex_buffer_[i], &vertex_out);
    vertex_out_buffer_.push_back(vertex_out);
  }

  primitive_assembler_->Reset();
  if (mode == DRAW_LINE) {
    for (int index = 0; index < element_buffer_.size() / 2; ++index) {
      LinePrimitive line;
      // primitive assemble stage
      if (primitive_assembler_->AssembleLine(element_buffer_[index * 2],
                                             element_buffer_[index * 2 + 1],
                                             &line) == false)
        continue;

      // rasterize stage
      rasterizer_->DrawLinePrimitive(line);

      // fragment shader stage
      FragmentOut fragment_shader_out;
      for (Fragment &fragment : fragment_buffer_) {
        fragment_shader_->Run(fragment, &fragment_shader_out);

        if (per_sample_processor_->Run(fragment_shader_out) == true) {
          // test fragment success, pass into framebuffer;
          SetPixelToWindow(fragment_shader_out.window_position.x,
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
      std::vector<TrianglePrimitive> triangles;
      primitive_assembler_->AssembleTriangle(
          element_buffer_[index * 3], element_buffer_[index * 3 + 1],
          element_buffer_[index * 3 + 2], &triangles);
      for (TrianglePrimitive &triangle : triangles) {
        rasterizer_->DrawTrianglePrimitive(triangle, polygon_mode_);

        FragmentOut fragment_shader_out;
        for (Fragment &fragment : fragment_buffer_) {
          fragment_shader_->Run(fragment, &fragment_shader_out);

          if (per_sample_processor_->Run(fragment_shader_out) == true) {
            // test fragment success, pass into framebuffer;
            SetPixelToWindow(fragment_shader_out.window_position.x,
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
  std::fill(frame_buffer_.begin(), frame_buffer_.end(), 10);
  std::fill(depth_buffer_.begin(), depth_buffer_.end(), 1.0);
}

RenderingPipeline::~RenderingPipeline() {}

// set pixel to window frame buffer
void RenderingPipeline::SetPixelToWindow(const int x, const int y,
                                         const math::vec4 &color) {
  if (0 <= x && x <= width_ && 0 <= y && y <= height_) {
    int offset = (y * width_ + x) * 4;
    frame_buffer_[offset] = math::Clamp(color.z * 255, 0, 255);      // b
    frame_buffer_[offset + 1] = math::Clamp(color.y * 255, 0, 255);  // g
    frame_buffer_[offset + 2] = math::Clamp(color.x * 255, 0, 255);  // r
    frame_buffer_[offset + 3] = math::Clamp(color.w * 255, 0, 255);  // a
  }
}

// set depth buffer value
void RenderingPipeline::SetDepth(const int x, const int y, const float z) {
  depth_buffer_[y * width_ + x] = z;
}

std::vector<uint8_t> *RenderingPipeline::GetFrameBufferPtr() {
  return &frame_buffer_;
}

}  // namespace softrd
