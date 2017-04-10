#include "renderer.h"

namespace softrd {


Renderer::Renderer(const int width, const int height) : 
width_(width), 
height_(height),
vertex_shader_(),
vertex_post_processor_(width, height),
primitve_assembler_(),
rasterizer_(width, height),
per_sample_proccessor_(),
device_(100, 100, width, height) {
    vertex_buffer_ = new Vertex[1000];
    element_buffer_ = new int[1000];
    vertex_out_buffer_ = new VertexOut[1000];
    fragment_buffer_ = new std::vector<Fragment>();
    frame_buffer_ = new vec4[width * height];
    depth_buffer_ = new float[width * height];

    device_.Setup();
}

void Renderer::Run() {

}

void Renderer::Draw() {

    Camera camera((float)width_ / (float)height_);

    mat4 model;
    model.identify();
    vertex_shader_.model_ = model;
    vertex_shader_.view_ = camera.view;
    vertex_shader_.projection_ = camera.projection;
    vertex_shader_.transform_ = camera.projection * camera.view * model;

    int vertex_num = 3;
    Vertex v1, v2, v3;
    v1.position = vec3(0, 0, 0);
    v2.position = vec3(2, 0, 0);
    v3.position = vec3(1, 3, 0);
    vertex_buffer_[0] = v1;
    vertex_buffer_[1] = v2;
    vertex_buffer_[2] = v3;
    for (int i = 0; i < vertex_num; i++)
        element_buffer_[i] = i;


    for (int i = 0; i < vertex_num; i++) {
        //vertex shader stage
        VertexShaderOut vs_out = vertex_shader_.Run(vertex_buffer_[i]);

        //vertex post processing stage
        VertexOut vertex_out = vertex_post_processor_.Run(vs_out);
        vertex_out_buffer_[i] = vertex_out;

    }

    for (int triangle_index = 0; triangle_index < vertex_num / 3; ++triangle_index) {
        VertexOut &vo1 = vertex_out_buffer_[triangle_index * 3];
        VertexOut &vo2 = vertex_out_buffer_[triangle_index * 3 + 1];
        VertexOut &vo3 = vertex_out_buffer_[triangle_index * 3 + 2];
        TrianglePrimitive triangle = primitve_assembler_.AssembleTriangle(vo1, vo2, vo3);

        rasterizer_.DrawTriangle(triangle, fragment_buffer_);

        for (Fragment fragment : *fragment_buffer_) {
            fragment_shader_.in_ = fragment;
            fragment_shader_.Run();
            per_sample_proccessor_.in_ = fragment_shader_.out_;
            if (per_sample_proccessor_.Run() == true) {
                // test fragment success, pass into framebuffer;
                SetPixel(fragment_shader_.out_.window_position.x, fragment_shader_.out_.window_position.y, fragment_shader_.out_.color);
            }
        }
    }


    for (Fragment fragment : *fragment_buffer_) {
        fragment_shader_.in_ = fragment;
        fragment_shader_.Run();
        per_sample_proccessor_.in_ = fragment_shader_.out_;
        if (per_sample_proccessor_.Run() == true) {
            // test fragment success, pass into framebuffer;
            SetPixel(fragment_shader_.out_.window_position.x, fragment_shader_.out_.window_position.y, fragment_shader_.out_.color);
        }
    }

    for (int i = 0; i < 10; i++) {
        device_.Draw(frame_buffer_);
    }


}

Renderer::~Renderer() {
}

void Renderer::SetPixel(const int x, const int y, const vec4 &color) {
    if (0 <= x && x <= width_ && 0 <= y && y <= height_) {
        frame_buffer_[y * width_ + x] = color;
    }
}

} // namespace softrd

