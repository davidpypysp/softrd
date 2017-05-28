#include "renderer.h"
#include "model.h"
#include "vertex_loader.h"



namespace softrd {


Renderer::Renderer(const int width, const int height) : 
width_(width), 
height_(height),
screen_size_(width * height),
primitve_assembler_(width, height),
rasterizer_(width, height),
per_sample_proccessor_(width, height),
device_(100, 100, width, height),
camera_((float)width / (float)height),
polygon_mode(Rasterizer::TRIANGLE_FILL) {
    vertex_out_buffer_ = nullptr;
    fragment_buffer_ = new std::vector<Fragment>();
    frame_buffer_ = new unsigned char[screen_size_ * 4];
    depth_buffer_ = new float[screen_size_];

    rasterizer_.Setup(fragment_buffer_, &camera_);
    per_sample_proccessor_.Setup(depth_buffer_);
    device_.Setup();
    last_time_ = steady_clock::now();
}

void Renderer::Run() {
    LoadModel();

	VertexShaderLight vertex_shader;
	FragmentShader fragment_shader;
	FragmentShader1 fragment_shader_1;



    while (device_.Quit() == false) { // renderer main loop, implement rendering pipeline here
        // frame setting
        auto current_time = steady_clock::now();
        duration<double, std::milli> time_span = current_time - last_time_;
        delta_time_ = time_span.count();
        fps_ = (int)(1000.0 / delta_time_);
        frame_count_++;
        last_time_ = current_time;

        // reset buffer
        memset(frame_buffer_, 0, sizeof(unsigned char) * screen_size_ * 4);
        std::fill(depth_buffer_, depth_buffer_ + screen_size_, 1.0);

        // handle input
        HandleInput();


		// first cube
        mat4 model_matrix;
        model_matrix.identify();
        vertex_shader.model_ = model_matrix;
        //vertex_shader.view_ = camera_.view;
        //vertex_shader.projection_ = camera_.projection;
        vertex_shader.transform_ = camera_.projection * camera_.view * model_matrix;

		SetShader(&vertex_shader, &fragment_shader);
		SetPolygonMode(Rasterizer::TRIANGLE_FILL);
		Draw(DRAW_LINE);

		// second cube
		model_matrix[0][3] = 3.0;
		model_matrix[1][3] = 1.0;
		model_matrix[2][3] = 1.0;
		vertex_shader.model_ = model_matrix;
		vertex_shader.transform_ = camera_.projection * camera_.view * model_matrix;

		SetShader(&vertex_shader, &fragment_shader_1);
		SetPolygonMode(Rasterizer::TRIANGLE_LINE);
		Draw(DRAW_TRIANGLE);


        // draw everything in the device
        device_.RenderClear();
        device_.Draw(frame_buffer_);
        device_.DrawText("FPS: " + std::to_string(fps_), 2, 2, 90, 30);
        //device_.DrawText("Frame: " + std::to_string(frame_count_), 2, 32, 200, 30);
        device_.RenderPresent();

    }


    Clear();

}

void Renderer::SetShader(VertexShader *vertex_shader, FragmentShader *fragment_shader) {
	vertex_shader_ = vertex_shader;
	fragment_shader_ = fragment_shader;
}

void Renderer::Draw(const DrawMode mode) { // rendering pipeline
	for (int i = 0; i < vertex_buffer_.size(); i++) {
		//vertex shader stage
		vertex_shader_->Run(vertex_buffer_[i], &vertex_out_buffer_[i]);
	}

	primitve_assembler_.Reset();
	if (mode == DRAW_LINE) {
		for (int index = 0; index < element_buffer_.size() / 2; ++index) {
			LinePrimitive line;
			if (primitve_assembler_.AssembleLine(element_buffer_[index * 2], element_buffer_[index * 2 + 1], &line) == false) continue;

			rasterizer_.DrawLinePrimitive(line);
			FragmentOut fragment_shader_out;
			for (Fragment &fragment : *fragment_buffer_) {
				fragment_shader_->Run(fragment, &fragment_shader_out);
				if (per_sample_proccessor_.Run(fragment_shader_out) == true) {
					// test fragment success, pass into framebuffer;
					SetPixel(fragment_shader_out.window_position.x, fragment_shader_out.window_position.y, fragment_shader_out.color);
					SetDepth(fragment_shader_out.window_position.x, fragment_shader_out.window_position.y, fragment_shader_out.window_position.z);
				}
			}

		}
	}
	else if (mode == DRAW_TRIANGLE) {
		for (int index = 0; index < element_buffer_.size() / 3; ++index) {
			std::vector<TrianglePrimitive> triangles;
			primitve_assembler_.AssembleTriangle(element_buffer_[index * 3], element_buffer_[index * 3 + 1], element_buffer_[index * 3 + 2], &triangles);

			for (TrianglePrimitive &triangle : triangles) {
				rasterizer_.DrawTrianglePrimitive(triangle, polygon_mode);

				FragmentOut fragment_shader_out;
				for (Fragment &fragment : *fragment_buffer_) {
					fragment_shader_->Run(fragment, &fragment_shader_out);
					if (per_sample_proccessor_.Run(fragment_shader_out) == true) {
						// test fragment success, pass into framebuffer;
						SetPixel(fragment_shader_out.window_position.x, fragment_shader_out.window_position.y, fragment_shader_out.color);
						SetDepth(fragment_shader_out.window_position.x, fragment_shader_out.window_position.y, fragment_shader_out.window_position.z);
					}
				}
			}
		}
	}

}

void Renderer::SetPolygonMode(const Rasterizer::DrawTriangleMode mode) {
	polygon_mode = mode;
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
        frame_buffer_[offset+1] = color.y * 255 ; // g
        frame_buffer_[offset+2] = color.x * 255; // r
        frame_buffer_[offset+3] = 255; // a 
    }
}

void Renderer::SetDepth(const int x, const int y, const float z) {
    depth_buffer_[y * width_ + x] = z;
}

void Renderer::LoadModel() {
	VertexLoader loader;

	//loader.LoadTriangle(vertex_buffer_, element_buffer_);
	loader.LoadCube(vertex_buffer_, element_buffer_);

#define MODEL 0
#if MODEL
	Model model("resource/cruiser/cruiser.obj");
	//Model model("resource/f-16/f-16.obj");
	//Model model("resource/wt_teapot.obj");
	for (Mesh &mesh : model.meshes) {
		for (Vertex &vertex : mesh.vertices) vertex_buffer_.push_back(vertex);
		for (Uint32 index : mesh.indices) element_buffer_.push_back(index);
	}


#endif


#define TRIANGLE2 0
#if TRIANGLE2
	Vertex v1, v2, v3, v4;
	v1.position = vec3(-0.5, 0.0, 0);
	v2.position = vec3(-0.5, 1.0, 0);
	v3.position = vec3(0.5, 0.0, 0);
	v4.position = vec3(0.5, 1.0, 0);

	v1.uv = vec2(0.0, 1.0);
	v2.uv = vec2(0.0, 0.0);
	v3.uv = vec2(1.0, 1.0);
	v4.uv = vec2(1.0, 0.0);

	vertex_buffer_.push_back(v1);
	vertex_buffer_.push_back(v2);
	vertex_buffer_.push_back(v3);
	vertex_buffer_.push_back(v4);

	element_buffer_.push_back(0);
	element_buffer_.push_back(1);
	element_buffer_.push_back(2);

	element_buffer_.push_back(1);
	element_buffer_.push_back(2);
	element_buffer_.push_back(3);

#endif





	//Texture *texture = new Texture("resource/img_cheryl.jpg");
	//Texture *texture = new Texture("resource/mini.jpg");
    //Texture *texture = new Texture("resource/test_rect.png");
    //Texture *texture = new Texture("resource/container.jpg");

	vertex_out_buffer_ = new VertexOut[vertex_buffer_.size()];
    primitve_assembler_.Setup(vertex_buffer_.size(), vertex_out_buffer_);

}


void Renderer::HandleInput() {
    device_.HandleEvents();

    float move_step = 0.05;
    vec3 move;
    if (device_.PressKeyW()) move.z -= move_step;
    if (device_.PressKeyS()) move.z += move_step;
    if (device_.PressKeyA()) move.x -= move_step;
    if (device_.PressKeyD()) move.x += move_step;
    camera_.Move(move);

    float degree = 1.5;
    vec3 rotate;
    if (device_.PressKeyUp()) rotate.x -= degree;
    if (device_.PressKeyDown()) rotate.x += degree;
    if (device_.PressKeyLeft()) rotate.y -= degree;
    if (device_.PressKeyRight()) rotate.y += degree;
    camera_.Rotate(rotate);


    if (device_.PressKeyQ()) camera_.Zoom(-degree);
    if (device_.PressKeyE()) camera_.Zoom(degree);
}

} // namespace softrd

