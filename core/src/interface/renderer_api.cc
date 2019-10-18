#include "src/interface/renderer_api.h"

namespace softrd {
RendererAPI::RendererAPI() : rendering_pipeline_(640, 480) {}

void RendererAPI::InitExampleMesh() {
  // define cube
  example_cube_.LoadCube2();

  // define shaders
  VertexShaderLight vertex_shader_light;
  FragmentShaderFlatColor fragment_shader;
  FragmentShaderLightFull fragment_shader_light(camera_.position,
                                                object_material);

  FragmentShaderLightTexture fragment_shader_light_texture(camera_.position,
                                                           object_material2);
  fragment_shader_light_texture.AddLight(&light);
}

RendererAPI::DrawExampleMesh() {
  mat4 model_matrix;

  // 1. cube object
  model_matrix.identify();
  model_matrix.translate(vec3(0.0, 0.0, 0.0));
  vertex_shader_light.model_ = model_matrix;
  vertex_shader_light.transform_ =
      camera_.projection * camera_.view * model_matrix;

  rendering_pipeline_.DrawMesh(example_cube_, vertex_shader_light,
                               fragment_shader_light, Rasterizer::TRIANGLE_FILL,
                               DRAW_TRIANGLE);
}

RendererAPI::~RendererAPI() {}

}  // namespace softrd
