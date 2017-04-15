#ifndef SOFTRD_DEVICE_H_
#define SOFTRD_DEVICE_H_

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include "math/vector.h"



namespace softrd {
	
// package the sdl library windows function
class Device {
public:
	Device(const int x_pos, const int y_pos, const int width, const int height);
	int Setup();
	void Draw(unsigned char *frame_buffer);
	void HandleEvents();
	~Device();

	bool quit() { return quit_; }

	bool PressKeyUp();
	bool PressKeyDown();
	bool PressKeyLeft();
	bool PressKeyRight();
	bool PressKeyW();
	bool PressKeyS();
	bool PressKeyA();
	bool PressKeyD();



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