#include "src/interface/renderer_api.h"

namespace softrd {
RendererAPI::RendererAPI() : rendering_pipeline_(640, 480) {}

void RendererAPI::InitExampleMesh() {
  // define cube
  example_cube_.LoadCube2();
}

void RendererAPI::DrawExampleMesh() {
  mat4 model_matrix;

  // define shaders
  VertexShaderLight vertex_shader;
  FragmentShaderFlatColor fragment_shader;

  const auto& camera = rendering_pipeline_.camera();

  // 1. cube object
  model_matrix.identify();
  model_matrix.translate(vec3(0.0, 0.0, 0.0));
  vertex_shader.model_ = model_matrix;
  vertex_shader.transform_ = camera.projection * camera.view * model_matrix;

  rendering_pipeline_.DrawMesh(example_cube_, vertex_shader, fragment_shader,
                               Rasterizer::TRIANGLE_FILL,
                               RenderingPipeline::DrawMode::DRAW_TRIANGLE);
}

RendererAPI::~RendererAPI() {}

}  // namespace softrd
