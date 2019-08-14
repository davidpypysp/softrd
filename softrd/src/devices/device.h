#ifndef SOFTRD_DEVICE_H_
#define SOFTRD_DEVICE_H_

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include <string>
#include "math/vector.h"
#include "util.h"



namespace softrd {
	
// package the sdl library windows function
class Device {
public:
	Device(const int x_pos, const int y_pos, const int width, const int height);
	int Setup();
	void Draw(util::Array<unsigned char> &frame_buffer);
	void DrawTextFixed(const std::string &str, const int x, const int y, const int width, const int height);
	void DrawText(const std::string &str, const float x, const float y, const int size = 25, const vec4 &color = vec4(255, 255, 255, 0));
	void HandleEvents();
	void RenderClear();
	void RenderPresent();
	~Device();

	bool Quit();

	bool PressKeyUp();
	bool PressKeyDown();
	bool PressKeyLeft();
	bool PressKeyRight();
	bool PressKeyW();
	bool PressKeyS();
	bool PressKeyA();
	bool PressKeyD();
	bool PressKeyQ();
	bool PressKeyE();
	bool PressKeyR();
	bool PressKeyI();
	bool PressKeyK();
	bool PressKeyJ();
	bool PressKeyL();




private:


	int width_, height_;
	int x_pos_, y_pos_;
	SDL_Window *window_;
	SDL_Renderer *renderer_;
	SDL_Event sdl_event_;
	SDL_Texture *texture_;
	bool keys_[512];
	bool quit_ = false;
};

} // namespace softrd


#endif // SOFTRD_DEVICE_H_