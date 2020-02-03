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
  example_cube_->LoadCube2();
}

void RendererAPI::DrawExampleMesh() {
  auto &camera = rendering_pipeline_->camera();

  // ----------------- define procedure ------------------------

  // define object
  Mesh object;
  object.LoadCube2();

  Material object_material(vec3(1.0, 1.0, 1.0), vec3(1.0, 0.5, 0.31),
                           vec3(0.5, 0.5, 0.5), 32.0);

  Mesh spot_light_lamp;
  spot_light_lamp.LoadCube();
  SpotLight spot_light(vec3(3.0, 0.0, 0.0), vec3(-1.0, 0.0, 0.0),
                       cos(Radians(12.5)), cos(Radians(17.5)),
                       vec3(0.1, 0.1, 0.1), vec3(0.8, 0.8, 0.8),
                       vec3(1.0, 1.0, 1.0), 1.0, 0.09, 0.032);

  // define shaders
  VertexShaderLight vertex_shader_light;

  FragmentShader fragment_shader;
  FragmentShaderLightFull fragment_shader_light(camera.position,
                                                object_material);
  fragment_shader_light.AddLight(&spot_light);

  // ----------------- draw procedure ------------------------
  mat4 model_matrix;

  // // 1. cube object
  // model_matrix.identify();
  // model_matrix.translate(vec3(0.0, 0.0, 0.0));

  // vertex_shader_light.model_ = model_matrix;
  // vertex_shader_light.transform_ =
  //     camera.projection * camera.view * model_matrix;

  // std::cout << "draw mesh" << std::endl;
  // rendering_pipeline_->DrawMesh(
  //     object, vertex_shader_light, fragment_shader_light,
  //     Rasterizer::TRIANGLE_FILL, RenderingPipeline::DrawMode::DRAW_TRIANGLE);

  // 4. spot light lamp
  model_matrix.identify();
  model_matrix.scale(0.1, 0.1, 0.1);
  model_matrix.translate(spot_light.position);
  vertex_shader_light.model_ = model_matrix;
  vertex_shader_light.transform_ =
      camera.projection * camera.view * model_matrix;
  rendering_pipeline_->DrawMesh(spot_light_lamp, vertex_shader_light,
                                fragment_shader, Rasterizer::TRIANGLE_FILL);
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
