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
polygon_mode_(Rasterizer::TRIANGLE_FILL) {
    rasterizer_.SetCamera(&camera_);
    device_.Setup();
    last_time_ = steady_clock::now();
	inputs_.push_back(new InputUnit3("Camera", &camera_.position));
	inputs_.push_back(new InputUnit3("Camera Direction", &camera_.direction));
    input_index_ = 0;
}

void Renderer::Run() {
    LoadCoordinateAxis();
    

    // define object
    Mesh object;
    object.LoadCube2();
    vec3 object_position = vec3(0.0, 0.0, 0.0);
    inputs_.push_back(new InputUnit3("Object", &object_position));
	vec3 object2_position = vec3(3.0, 0.0, 0.0);
	inputs_.push_back(new InputUnit3("Object2", &object2_position));
    Material object_material(vec3(1.0, 0.5, 0.31), vec3(1.0, 0.5, 0.31), vec3(0.5, 0.5, 0.5), 32.0);
    Texture *diffuse_texture = new Texture("resource/container2.png");
	Texture *specular_texture = new Texture("resource/container2_specular.png");
    TextureMaterial object_material2(diffuse_texture, specular_texture, 32.0);

    // define lamp light
    Mesh light_lamp;
    light_lamp.LoadCube();
    Light light(vec3(0.0, 0.0, 3.0), vec3(0.2, 0.2, 0.2), vec3(0.5, 0.5, 0.5), vec3(1.0, 1.0, 1.0));
    inputs_.push_back(new InputUnit3("Light", &light.position));


	// define directional light
	DirLight dir_light(vec3(-0.2, -1.0, -0.3), vec3(0.05, 0.05, 0.05), vec3(0.4, 0.4, 0.4), vec3(0.5, 0.5, 0.5));
	inputs_.push_back(new InputUnit3("DirLight Direction", &dir_light.direction));


	// define lamp point light
	Mesh point_light_lamp;
	point_light_lamp.LoadCube();
	PointLight point_light(vec3(-3.0, 0.0, 0.0), vec3(0.05, 0.05, 0.05), vec3(0.8, 0.8, 0.8), vec3(1.0, 1.0, 1.0), 1.0, 0.09, 0.032);
	inputs_.push_back(new InputUnit3("PointLight", &point_light.position));

	// difine lamp spot light
	Mesh spot_light_lamp;
	spot_light_lamp.LoadCube();
	SpotLight spot_light(vec3(3.0, 0.0, 0.0), vec3(-1.0, 0.0, 0.0), cos(Radians(12.5)), cos(Radians(17.5)), vec3(0.1, 0.1, 0.1), vec3(0.8, 0.8, 0.8), vec3(1.0, 1.0, 1.0), 1.0, 0.09, 0.032);
	inputs_.push_back(new InputUnit3("SpotLight", &spot_light.position));

	// define shaders
    VertexShaderLight vertex_shader_light;
    FragmentShader fragment_shader;
    FragmentShaderLightFull fragment_shader_light(camera_.position, object_material, light);
    FragmentShaderLightTexture fragment_shader_light_texture(camera_.position, object_material2);
	fragment_shader_light_texture.AddLight(&light);
	fragment_shader_light_texture.AddLight(&dir_light);
	fragment_shader_light_texture.AddLight(&point_light);
	fragment_shader_light_texture.AddLight(&spot_light);


    while (device_.Quit() == false) { // renderer main loop, implement rendering pipeline here
        // frame setting
        SetFrame();

        // reset buffer
        ResetBuffer();

        // handle input
        Input();

        // draw cordinate system
        DrawCoordinateAxis();

        
        // -------------------------------------------------------------------------------

		// update camera spot light
		//spot_light.position = camera_.position;
		//spot_light.direction = -camera_.direction;

		mat4 model_matrix;

        
        // 1. cube object


        model_matrix.identify();
        model_matrix.translate(object_position);
        vertex_shader_light.model_ = model_matrix;
        vertex_shader_light.transform_ = camera_.projection * camera_.view * model_matrix;

		DrawObject(object, vertex_shader_light, fragment_shader_light_texture, Rasterizer::TRIANGLE_FILL, DRAW_TRIANGLE);

        

        // 2. light lamp
        model_matrix.identify();
        model_matrix.scale(0.1, 0.1, 0.1);
        model_matrix.translate(light.position);
        vertex_shader_light.model_ = model_matrix;
        vertex_shader_light.transform_ = camera_.projection * camera_.view * model_matrix;

		DrawObject(light_lamp, vertex_shader_light, fragment_shader);

		
		// 3. point light lamp
		model_matrix.identify();
		model_matrix.scale(0.1, 0.1, 0.1);
		model_matrix.translate(point_light.position);
		vertex_shader_light.model_ = model_matrix;
		vertex_shader_light.transform_ = camera_.projection * camera_.view * model_matrix;

		DrawObject(point_light_lamp, vertex_shader_light, fragment_shader);


		// 4. spot light lamp
		model_matrix.identify();
		model_matrix.scale(0.1, 0.1, 0.1);
		model_matrix.translate(spot_light.position);
		vertex_shader_light.model_ = model_matrix;
		vertex_shader_light.transform_ = camera_.projection * camera_.view * model_matrix;

		DrawObject(spot_light_lamp, vertex_shader_light, fragment_shader);


        // -------------------------------------------------------------------------------
        


        // draw everything in the device
        DrawFrame();
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
                rasterizer_.DrawTrianglePrimitive(triangle, polygon_mode_);

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

void Renderer::DrawObject(Mesh &mesh, VertexShader &vertex_shader, FragmentShader &fragment_shader, const Rasterizer::DrawTriangleMode tri_mode, const DrawMode draw_mode) {
	mesh.LoadBuffer(vertex_buffer_, element_buffer_);
	SetShader(&vertex_shader, &fragment_shader);
	SetPolygonMode(tri_mode);
	Draw(draw_mode);
}

void Renderer::SetPolygonMode(const Rasterizer::DrawTriangleMode mode) {
    polygon_mode_ = mode;
}

void Renderer::ResetBuffer() {
    frame_buffer_.Fill(10);
    depth_buffer_.Fill(1.0);

}

void Renderer::Clear() {
}

Renderer::~Renderer() {
}

void Renderer::SetPixel(const int x, const int y, const vec4 &color) {
    if (0 <= x && x <= width_ && 0 <= y && y <= height_) {
        int offset = (y * width_ + x) * 4;
        frame_buffer_[offset] = Clamp(color.z * 255, 0, 255); // b
        frame_buffer_[offset+1] = Clamp(color.y * 255, 0, 255); // g
        frame_buffer_[offset+2] = Clamp(color.x * 255, 0, 255); // r
        frame_buffer_[offset+3] = Clamp(color.w * 255, 0, 255); // a 
    }
}

void Renderer::SetDepth(const int x, const int y, const float z) {
    depth_buffer_[y * width_ + x] = z;
}

void Renderer::SetFrame() {
    // frame setting
    auto current_time = steady_clock::now();
    duration<double, std::milli> time_span = current_time - last_time_;
    delta_time_ = time_span.count();
    fps_ = 1000.0 / delta_time_;
    frame_count_++;
    last_time_ = current_time;
}

void Renderer::SetUI() {
    //device_.DrawText("FPS: " + util::ToString(fps_, 1), 2, 2, 100, 30);
    std::string fps_info = "FPS: " + util::ToString(fps_, 1);
    device_.DrawText(fps_info, 0.01, 0.005, 23);

    std::string input_info = inputs_[input_index_]->Info();
    device_.DrawText(input_info, 0.01, 0.94, 23);
    //device_.DrawText("Frame: " + std::to_string(frame_count_), 2, 32, 200, 30);
}

void Renderer::DrawFrame() {
    device_.RenderClear();
    device_.Draw(frame_buffer_);
    SetUI();
    device_.RenderPresent();
}



void Renderer::Input() {
    device_.HandleEvents();

    // change object
    if (device_.PressKeyR()) {
        input_index_ += kPressValue;
        if (input_index_ >= inputs_.size()) input_index_ = 0;
    }
    else {
        input_index_ = floor(input_index_);
    }

    // move object
    float move_step = 0.05;
    vec4 move;
    if (device_.PressKeyW()) move.z -= move_step;
    if (device_.PressKeyS()) move.z += move_step;
    if (device_.PressKeyA()) move.x -= move_step;
    if (device_.PressKeyD()) move.x += move_step;
    if (device_.PressKeyI()) move.y += move_step;
    if (device_.PressKeyK()) move.y -= move_step;
    if (device_.PressKeyJ()) move.w -= move_step;
    if (device_.PressKeyL()) move.w += move_step;


    if ((int)input_index_ == 0) { // move camera
        camera_.Move(move.getVec3());
    }
    else { // move other position
        inputs_[input_index_]->Move(move);
    }


    // rotate camera
    float degree = 1.5;
    vec3 rotate;
    if (device_.PressKeyUp()) rotate.x -= degree;
    if (device_.PressKeyDown()) rotate.x += degree;
    if (device_.PressKeyLeft()) rotate.y -= degree;
    if (device_.PressKeyRight()) rotate.y += degree;
    camera_.Rotate(rotate);


    // fov setting
    if (device_.PressKeyQ()) camera_.Zoom(-degree);
    if (device_.PressKeyE()) camera_.Zoom(degree);
}

bool Renderer::Press() {
    return false;
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

