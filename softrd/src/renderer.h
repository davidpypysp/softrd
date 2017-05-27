#ifndef SOFTRD_RENDERER_H_
#define SOFTRD_RENDERER_H_

#include <vector>
#include <chrono>


#include "camera.h"
#include "vertex_shader.h"
#include "rasterizer.h"
#include "fragment_shader.h"
#include "per_sample_processing.h"
#include "device.h"

using namespace std::chrono;

namespace softrd {

// Renderer class deals with the whole process of rendering pipeline
// It start from reading .obj file to finally set the frame buffer to the screen
class Renderer {
public:
	Renderer(const int width, const int height);
	void Run();
	void SetShader(VertexShader *vertex_shader, FragmentShader *fragment_shader);
	void Draw(const Rasterizer::DrawTriangleMode mode); // draw one frame
	void Clear();
	~Renderer();



private:

	void SetPixel(const int x, const int y, const vec4 &color);
	void SetDepth(const int x, const int y, const float z);
	void LoadModel();
	void LoadCube();
	void HandleInput();

	int width_, height_, screen_size_;

	// frame setting
	time_point<steady_clock> last_time_;
	double delta_time_;
	int fps_;
	int frame_count_;
	
	// pipeline stages
	VertexShader *vertex_shader_;
	FragmentShader *fragment_shader_;

	PrimitiveAssembler primitve_assembler_;
	Rasterizer rasterizer_;
	PerSampleProcessor per_sample_proccessor_;
	Device device_;

	Camera camera_;

	// all buffers
	std::vector<Vertex> vertex_buffer_;
	std::vector<Uint32> element_buffer_;
	VertexOut *vertex_out_buffer_;
	std::vector<Fragment> *fragment_buffer_;
	unsigned char *frame_buffer_;
	float *depth_buffer_;


	
};


} // namespace softrd


#endif // SOFTRD_RENDERER_H_