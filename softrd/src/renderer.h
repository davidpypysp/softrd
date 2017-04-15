#ifndef SOFTRD_RENDERER_H_
#define SOFTRD_RENDERER_H_

#include <vector>

#include "camera.h"
#include "vertex_shader.h"
#include "rasterizer.h"
#include "fragment_shader.h"
#include "per_sample_processing.h"
#include "device.h"


namespace softrd {

// Renderer class deals with the whole process of rendering pipeline
// It start from reading .obj file to finally set the frame buffer to the screen
class Renderer {
public:
	Renderer(const int width, const int height);
	void Run();
	void Draw(); // draw one frame
	void Clear();
	~Renderer();



private:

	void SetPixel(const int x, const int y, const vec4 &color);

	int width_, height_;
	
	// pipeline stages
	VertexShader vertex_shader_;
	PrimitiveAssembler primitve_assembler_;
	Rasterizer rasterizer_;
	FragmentShader fragment_shader_;
	PerSampleProcessor per_sample_proccessor_;
	Device device_;

	// all buffers
	Vertex *vertex_buffer_;
	int *element_buffer_;
	VertexOut *vertex_out_buffer_;
	std::vector<Fragment> *fragment_buffer_;
	unsigned char *frame_buffer_;
	float *depth_buffer_;


	
};


} // namespace softrd


#endif // SOFTRD_RENDERER_H_