#include "renderer.h"
#include "model.h"
#include "vertex_loader.h"



namespace softrd {


Renderer::Renderer(const int width, const int height) : 
width_(width), 
height_(height),
screen_size_(width * height),
frame_buffer_(screen_size_ * 4),
depth_buffer_(screen_size_),
primitve_assembler_(width, height, vertex_out_buffer_),
rasterizer_(width, height, fragment_buffer_),
per_sample_proccessor_(width, height, depth_buffer_),
device_(100, 100, width, height),
camera_((float)width / (float)height),
polygon_mode(Rasterizer::TRIANGLE_FILL) {
    rasterizer_.SetCamera(&camera_);
    device_.Setup();
    last_time_ = steady_clock::now();
}

void Renderer::Run() {
	LoadCoordinateAxis();

	Mesh cube;
	cube.LoadCube();

	Mesh triangle;
	triangle.LoadTriangle();

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
		ResetFrameBuffer();
		depth_buffer_.Fill(1.0);

        // handle input
        Input();

		// draw cordinate system
		DrawCoordinateAxis();

		
		// -------------------------------------------------------------------------------
		
		// first cube
		cube.LoadBuffer(vertex_buffer_, element_buffer_);

        mat4 model_matrix;
        model_matrix.identify();
        vertex_shader.model_ = model_matrix;
        //vertex_shader.view_ = camera_.view;
        //vertex_shader.projection_ = camera_.projection;
        vertex_shader.transform_ = camera_.projection * camera_.view * model_matrix;

		SetShader(&vertex_shader, &fragment_shader);
		SetPolygonMode(Rasterizer::TRIANGLE_LINE);
		Draw(DRAW_TRIANGLE);
		

		// second triangle
		triangle.LoadBuffer(vertex_buffer_, element_buffer_);

		model_matrix[0][3] = 3.0;
		model_matrix[1][3] = 1.0;
		model_matrix[2][3] = 1.0;
		vertex_shader.model_ = model_matrix;
		vertex_shader.transform_ = camera_.projection * camera_.view * model_matrix;

		SetShader(&vertex_shader, &fragment_shader_1);
		SetPolygonMode(Rasterizer::TRIANGLE_LINE);
		Draw(DRAW_TRIANGLE);


		// -------------------------------------------------------------------------------
		


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
	//vertex shader stage
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
			if (primitve_assembler_.AssembleLine(element_buffer_[index * 2], element_buffer_[index * 2 + 1], &line) == false) continue; 

			// rasterize stage
			rasterizer_.DrawLinePrimitive(line);

			// fragment shader stage
			FragmentOut fragment_shader_out;
			for (Fragment &fragment : fragment_buffer_) {
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
				for (Fragment &fragment : fragment_buffer_) {
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

void Renderer::ResetFrameBuffer() {
	frame_buffer_.Fill(10);
}

void Renderer::Clear() {
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



void Renderer::Input() {
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

void Renderer::LoadCoordinateAxis() {
	axis_lines_[0].LoadLine(vec3(0, 0, 0), vec3(10, 0, 0), vec3(1, 0, 0));
	axis_lines_[1].LoadLine(vec3(0, 0, 0), vec3(0, 10, 0), vec3(0, 1, 0));
	axis_lines_[2].LoadLine(vec3(0, 0, 0), vec3(0, 0, 10), vec3(0, 0, 1));

	grid_line_x_.LoadLine(vec3(-10, 0, 0), vec3(10, 0, 0));
	grid_line_y_.LoadLine(vec3(0, 0, -10), vec3(0, 0, 10));

}

void Renderer::DrawCoordinateAxis() {
	VertexShader vertex_shader;
	vertex_shader.transform_ = camera_.projection * camera_.view;

	FragmentShaderFlatColor fragment_shader;

	SetShader(&vertex_shader, &fragment_shader);
	
	for (int i = 0; i < 3; ++i) {
		axis_lines_[i].LoadBuffer(vertex_buffer_, element_buffer_);
		fragment_shader.flat_color = axis_lines_[i].color;
		Draw(DRAW_LINE);
	}

	
	fragment_shader.flat_color = vec3(0.5, 0.5, 0.5);
	mat4 model;
	model.identify();
	grid_line_x_.LoadBuffer(vertex_buffer_, element_buffer_);
	for (int z = -10; z <= 10; z += 2) {
		model[2][3] = z;
		vertex_shader.transform_ = camera_.projection * camera_.view * model;
		Draw(DRAW_LINE);
	}
	model[2][3] = 0;

	grid_line_y_.LoadBuffer(vertex_buffer_, element_buffer_);
	for (int x = -10; x <= 10; x += 2) {
		model[0][3] = x;
		vertex_shader.transform_ = camera_.projection * camera_.view * model;
		Draw(DRAW_LINE);
	}

}

} // namespace softrd

