#include "src/interface/renderer_api.h"

namespace softrd {
RendererAPI::RendererAPI() {
  std::cout << "renderer api constructor()" << std::endl;
  example_cube_ = new Mesh();
  rendering_pipeline_ = new RenderingPipeline(640, 480);
}

void RendererAPI::InitExampleMesh() {
  // define cube
  std::cout << "InitExampleMesh" << std::endl;
  example_cube_->LoadCube();
}

void RendererAPI::DrawExampleMesh() {
  mat4 model_matrix;

  // define shaders
  VertexShaderLight vertex_shader;
  FragmentShaderFlatColor fragment_shader;

  const auto &camera = rendering_pipeline_->camera();

  // 1. cube object
  model_matrix.identify();
  model_matrix.translate(vec3(0.0, 0.0, 0.0));
  vertex_shader.model_ = model_matrix;
  vertex_shader.transform_ = camera.projection * camera.view * model_matrix;

  std::cout << "draw mesh" << std::endl;
  rendering_pipeline_->DrawMesh(*example_cube_, vertex_shader, fragment_shader,
                                Rasterizer::TRIANGLE_FILL,
                                RenderingPipeline::DrawMode::DRAW_TRIANGLE);
}

void RendererAPI::ExamplePrint() {
  std::cout << "I'm suvived!" << std::endl;
  std::cout << "node-gyp work!!!" << std::endl;
  Texture *specular_texture = new Texture("resource/container2_specular.png");

  Model *example_model = new Model();
}

void RendererAPI::ResetBuffer(uint8_t *buffer, size_t size) {
  std::cout << "reset buffer" << std::endl;

  for (size_t index = 0; index < size; index += 4) {
    buffer[index] = 150;      // red
    buffer[index + 1] = 150;  // green
    buffer[index + 2] = 50;   // blue
    buffer[index + 3] = 255;  // alpha
  }
}

RendererAPI::~RendererAPI() {}

}  // namespace softrd
