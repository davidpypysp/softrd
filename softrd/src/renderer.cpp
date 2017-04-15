#include "renderer.h"

namespace softrd {


Renderer::Renderer(const int width, const int height) : 
width_(width), 
height_(height),
vertex_shader_(),
primitve_assembler_(width_, height_),
rasterizer_(width, height),
per_sample_proccessor_(),
device_(100, 100, width, height) {
    vertex_buffer_ = new Vertex[1000];
    element_buffer_ = new int[1000];
    vertex_out_buffer_ = new VertexOut[1000];
    fragment_buffer_ = new std::vector<Fragment>();
    frame_buffer_ = new unsigned char[width * height * 4];
    depth_buffer_ = new float[width * height];

    device_.Setup();
}

void Renderer::Run() {
    Camera camera((float)width_ / (float)height_);

    while (device_.quit() == false) {
        device_.HandleEvents();


		// input handling
        vec3 move;
        if (device_.PressKeyW()) move.z -= 0.05;
        if (device_.PressKeyS()) move.z += 0.05;
        if (device_.PressKeyA()) move.x -= 0.05;
        if (device_.PressKeyD()) move.x += 0.05;
		camera.Move(move);

		vec3 rotate;
		if (device_.PressKeyUp()) rotate.x += 0.5;
		if (device_.PressKeyDown()) rotate.x -= 0.5;
		if (device_.PressKeyLeft()) rotate.y -= 0.5;
		if (device_.PressKeyRight()) rotate.y += 0.5;
		camera.Rotate(rotate);



        // set vertex buffer
        int vertex_num = 3;
        Vertex v1, v2, v3;
        v1.position = vec3(0, 0, 0);
        v2.position = vec3(2, 0, 0);
        v3.position = vec3(1, 1, 0);
        vertex_buffer_[0] = v1;
        vertex_buffer_[1] = v2;
        vertex_buffer_[2] = v3;
        // set element buffer
        for (int i = 0; i < vertex_num; i++)
            element_buffer_[i] = i;

        // set vertex shader
        mat4 model;
        model.identify();
        vertex_shader_.model_ = model;
		vertex_shader_.view_ = camera.view;
		vertex_shader_.projection_ = camera.projection;
        vertex_shader_.transform_ = camera.projection * camera.view * model;

        for (int i = 0; i < vertex_num; i++) {
            //vertex shader stage
            vertex_out_buffer_[i] = vertex_shader_.Run(vertex_buffer_[i]);
        }

        for (int triangle_index = 0; triangle_index < vertex_num / 3; ++triangle_index) {
            VertexOut &vo1 = vertex_out_buffer_[triangle_index * 3];
            VertexOut &vo2 = vertex_out_buffer_[triangle_index * 3 + 1];
            VertexOut &vo3 = vertex_out_buffer_[triangle_index * 3 + 2];
            std::vector<TrianglePrimitive> triangles = primitve_assembler_.AssembleTriangle(vo1, vo2, vo3);

			for (TrianglePrimitive triangle : triangles) {
				rasterizer_.DrawTriangle(triangle, fragment_buffer_, Rasterizer::TRIANGLE_LINE);

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


        }


        device_.Draw(frame_buffer_);
        memset(frame_buffer_, 0, sizeof(unsigned char) * width_ * height_ * 4);

    }




}

void Renderer::Draw() {


}

Renderer::~Renderer() {
}

void Renderer::SetPixel(const int x, const int y, const vec4 &color) {
    if (0 <= x && x <= width_ && 0 <= y && y <= height_) {
        int offset = (y * width_ + x) * 4;
        frame_buffer_[offset] = color.z * 255; // b
        frame_buffer_[offset+1] = color.x * 255; // g
        frame_buffer_[offset+2] = color.y * 255; // r
        frame_buffer_[offset+3] = 255; // a 
    }
}

} // namespace softrd

