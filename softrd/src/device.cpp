#include "device.h"
#include <iostream>



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

	window_ = SDL_CreateWindow("Hello World!", x_pos_, y_pos_, width_, height_, SDL_WINDOW_SHOWN);
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
}

void Device::Draw(vec4 *frame_buffer) {
	// First clear the renderer
	SDL_RenderClear(renderer_);

	// Draw every pixel in the Window
	int index = 0;
	for (int y = 0; y < height_; y++) {
		for (int x = 0; x < width_; x++) {
			vec4& color = frame_buffer[index++];
			SDL_SetRenderDrawColor(renderer_, color.x * 255, color.y * 255, color.z * 255, color.w * 255);
			SDL_RenderDrawPoint(renderer_, x, y);
		}
	}

	// Update the screen
	SDL_RenderPresent(renderer_);

	SDL_Delay(1000);
}

Device::~Device() {
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
	SDL_Quit();
}


} // namespace softrd
