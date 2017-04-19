#include "renderer.h"
#include "model.h"

namespace softrd {


Renderer::Renderer(const int width, const int height) : 
width_(width), 
height_(height),
screen_size_(width * height),
vertex_shader_(),
primitve_assembler_(width, height),
rasterizer_(width, height),
per_sample_proccessor_(width, height),
device_(100, 100, width, height) {
	vertex_out_buffer_ = nullptr;
    fragment_buffer_ = new std::vector<Fragment>();
    frame_buffer_ = new unsigned char[screen_size_ * 4];
    depth_buffer_ = new float[screen_size_];
	per_sample_proccessor_.Setup(depth_buffer_);
    device_.Setup();
}

void Renderer::Run() {
    Camera camera((float)width_ / (float)height_);

#define TEAPOT 1

#if TEAPOT
	Model model("resource/cruiser/cruiser.obj");
	//Model teapot("resource/f-16/f-16.obj");
	//Model teapot("resource/nanosuit/nanosuit.obj");
	for (Mesh &mesh : model.meshes) {
		for (Vertex &vertex : mesh.vertices) vertex_buffer_.push_back(vertex);
		for (Uint32 index : mesh.indices) element_buffer_.push_back(index);
	}
#endif

#if !TEAPOT
	Vertex v1, v2, v3;
	v1.position = vec3(0, 0, 0);
	v2.position = vec3(0, 1, 0);
	v3.position = vec3(0.2, 0, -2);
	vertex_buffer_.push_back(v1);
	vertex_buffer_.push_back(v2);
	vertex_buffer_.push_back(v3);
	element_buffer_.push_back(0);
	element_buffer_.push_back(1);
	element_buffer_.push_back(2);
#endif

	vertex_out_buffer_ = new VertexOut[vertex_buffer_.size()];

    while (device_.Quit() == false) { // renderer main loop
		memset(frame_buffer_, 0, sizeof(unsigned char) * screen_size_ * 4);
		std::fill(depth_buffer_, depth_buffer_ + screen_size_, 1.0);

        device_.HandleEvents();


		// input handling
		float move_step = 0.05;
        vec3 move;
        if (device_.PressKeyW()) move.z -= move_step;
        if (device_.PressKeyS()) move.z += move_step;
        if (device_.PressKeyA()) move.x -= move_step;
        if (device_.PressKeyD()) move.x += move_step;
		camera.Move(move);

		float degree = 1.5;
		vec3 rotate;
		if (device_.PressKeyUp()) rotate.x -= degree;
		if (device_.PressKeyDown()) rotate.x += degree;
		if (device_.PressKeyLeft()) rotate.y -= degree;
		if (device_.PressKeyRight()) rotate.y += degree;
		camera.Rotate(rotate);


		if (device_.PressKeyQ()) camera.Zoom(-degree);
		if (device_.PressKeyE()) camera.Zoom(degree);



        mat4 model_matrix;
        model_matrix.identify();
        vertex_shader_.model_ = model_matrix;
		vertex_shader_.view_ = camera.view;
		vertex_shader_.projection_ = camera.projection;
        vertex_shader_.transform_ = camera.projection * camera.view * model_matrix;

        for (int i = 0; i < vertex_buffer_.size(); i++) {
            //vertex shader stage
            vertex_shader_.Run(vertex_buffer_[i], &vertex_out_buffer_[i]);
        }

        for (int triangle_index = 0; triangle_index < element_buffer_.size() / 3; ++triangle_index) {
            VertexOut &vo1 = vertex_out_buffer_[element_buffer_[triangle_index * 3]];
            VertexOut &vo2 = vertex_out_buffer_[element_buffer_[triangle_index * 3 + 1]];
            VertexOut &vo3 = vertex_out_buffer_[element_buffer_[triangle_index * 3 + 2]];
			std::vector<TrianglePrimitive> triangles;
            primitve_assembler_.AssembleTriangle(vo1, vo2, vo3, &triangles);

			for (TrianglePrimitive &triangle : triangles) {
				rasterizer_.DrawTriangle(triangle, fragment_buffer_, Rasterizer::TRIANGLE_LINE);

				FragmentOut fragment_shader_out;
				for (Fragment &fragment : *fragment_buffer_) {
					fragment_shader_.Run(fragment, &fragment_shader_out);
					if (per_sample_proccessor_.Run(fragment_shader_out) == true) {
						// test fragment success, pass into framebuffer;
						SetPixel(fragment_shader_out.window_position.x, fragment_shader_out.window_position.y, fragment_shader_out.color);
						SetDepth(fragment_shader_out.window_position.x, fragment_shader_out.window_position.y, fragment_shader_out.window_position.z);
					}
				}
			}


        }


        device_.Draw(frame_buffer_);

    }

	Clear();

}

void Renderer::Draw() {


}

void Renderer::Clear() {
	delete[] vertex_out_buffer_;
	delete fragment_buffer_;
	delete frame_buffer_;
	delete[] depth_buffer_;
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

void Renderer::SetDepth(const int x, const int y, const float z) {
	depth_buffer_[y * width_ + x] = z;
}

} // namespace softrd

