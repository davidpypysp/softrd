#include "device.h"
#include <iostream>
#include <string>



namespace softrd {

Device::Device(const int x_pos, const int y_pos, const int width, const int height) : 
	x_pos_(x_pos), 
	y_pos_(y_pos),
	width_(width),
	height_(height) {
}

int Device::Setup() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	window_ = SDL_CreateWindow("Softrd", x_pos_, y_pos_, width_, height_, SDL_WINDOW_SHOWN);
	if (window_ == nullptr) {
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	//Create a renderer that will draw to the window, -1 specifies that we want to load whichever
	//video driver supports the flags we're passing
	//Flags: SDL_RENDERER_ACCELERATED: We want to use hardware accelerated rendering
	//SDL_RENDERER_PRESENTVSYNC: We want the renderer's present function (update screen) to be
	//synchronized with the monitor's refresh rate
	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer_ == nullptr) {
		SDL_DestroyWindow(window_);
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	texture_ = SDL_CreateTexture(renderer_, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width_, height_);

}

void Device::Draw(unsigned char *frame_buffer) {
	// First clear the renderer
	SDL_RenderClear(renderer_);

	// Draw every pixel in the Window
	SDL_UpdateTexture(texture_, NULL, frame_buffer, width_ * 4);
	SDL_RenderCopy(renderer_, texture_, NULL, NULL);

	// Update the screen
	SDL_RenderPresent(renderer_);

}

void Device::HandleEvents() {
	while (SDL_PollEvent(&sdl_event_) != 0) {
		if (sdl_event_.type == SDL_QUIT) { // user request quest
			quit_ = true;
		}
		else if (sdl_event_.type == SDL_KEYDOWN) {
			keys_[sdl_event_.key.keysym.scancode] = true;
			//printf("Key Down: %d\n", sdl_event_.key.keysym.scancode);
		}
		else if (sdl_event_.type == SDL_KEYUP) {
			keys_[sdl_event_.key.keysym.scancode] = false;
			//printf("Key Up: %d\n", sdl_event_.key.keysym.scancode);

		}
		else if (sdl_event_.type == SDL_MOUSEMOTION) {

		}
	}

}

Device::~Device() {
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
	SDL_Quit();
}

bool Device::PressKeyUp() {
	return keys_[SDL_SCANCODE_UP];
}

bool Device::PressKeyDown() { 
	return keys_[SDL_SCANCODE_DOWN]; 
}

bool Device::PressKeyLeft() {
	return keys_[SDL_SCANCODE_LEFT]; 
}

bool Device::PressKeyRight() {
	return keys_[SDL_SCANCODE_RIGHT]; 
}







} // namespace softrd
