#include "device.h"
#include <iostream>
#include <string>

#include <SDL2/SDL_ttf.h>


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

	if (TTF_Init() != 0) {
		std::cout << "SDL_TTF Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	window_ = SDL_CreateWindow("Softrd", x_pos_, y_pos_, width_, height_, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (window_ == nullptr) {
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	//Create a renderer that will draw to the window, -1 specifies that we want to load whichever
	//video driver supports the flags we're passing
	//Flags: SDL_RENDERER_ACCELERATED: We want to use hardware accelerated rendering
	//SDL_RENDERER_PRESENTVSYNC: We want the renderer's present function (update screen) to be
	//synchronized with the monitor's refresh rate
	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED  | SDL_RENDERER_PRESENTVSYNC);
	if (renderer_ == nullptr) {
		SDL_DestroyWindow(window_);
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	texture_ = SDL_CreateTexture(renderer_, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width_, height_);

}

void Device::Draw(util::Array<unsigned char> &frame_buffer) {
	// Draw every pixel in the Window
	SDL_UpdateTexture(texture_, NULL, frame_buffer.values, width_ * 4);
	SDL_RenderCopy(renderer_, texture_, NULL, NULL);



}

void Device::DrawTextFixed(const std::string &str, const int x, const int y, const int width, const int height) {
	TTF_Font* font = TTF_OpenFont("resource/font/Lato-Light.ttf", 25); //this opens a font style and sets a size
	SDL_Color color = { 255, 255, 255, 0 };  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color
	SDL_Surface* surface = TTF_RenderText_Solid(font, str.c_str(), color); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
	SDL_Texture* message = SDL_CreateTextureFromSurface(renderer_, surface); //now you can convert it into a texture
	SDL_FreeSurface(surface);

	SDL_Rect rect; //create a rect
	rect.x = x;  //controls the rect's x coordinate 
	rect.y = y; // controls the rect's y coordinte
	rect.w = width; // controls the width of the rect
	rect.h = height; // controls the height of the rect

	SDL_RenderCopy(renderer_, message, NULL, &rect); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture
	SDL_DestroyTexture(message);
}

void Device::DrawText(const std::string &str, const float x, const float y, const int size, const vec4 &color) {
	TTF_Font* font = TTF_OpenFont("resource/font/Lato-Light.ttf", size); //this opens a font style and sets a size
	SDL_Color text_color = { color.x, color.y, color.z, color.w };  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color
	SDL_Surface* surface = TTF_RenderText_Solid(font, str.c_str(), text_color); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
	SDL_Texture* message = SDL_CreateTextureFromSurface(renderer_, surface); //now you can convert it into a texture
	SDL_FreeSurface(surface);

	int length = str.length();

	SDL_Rect rect; //create a rect
	rect.x = x * width_;  //controls the rect's x coordinate 
	rect.y = y * height_; // controls the rect's y coordinte
	rect.w = size * length * 0.5; // controls the width of the rect
	rect.h = size * 1.08; // controls the height of the rect

	SDL_RenderCopy(renderer_, message, NULL, &rect); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture
	SDL_DestroyTexture(message);
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

void Device::RenderClear() {
	// First clear the renderer
	SDL_RenderClear(renderer_);
}

void Device::RenderPresent() {
	// Update the screen
	SDL_RenderPresent(renderer_);
}

Device::~Device() {
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
	SDL_Quit();
}

bool Device::Quit()
{
	return keys_[SDL_SCANCODE_ESCAPE] || quit_;
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

bool Device::PressKeyW() {
	return keys_[SDL_SCANCODE_W];
}

bool Device::PressKeyS() {
	return keys_[SDL_SCANCODE_S];
}

bool Device::PressKeyA() {
	return keys_[SDL_SCANCODE_A];
}

bool Device::PressKeyD() {
	return keys_[SDL_SCANCODE_D];
}

bool Device::PressKeyQ() {
	return keys_[SDL_SCANCODE_Q];
}

bool Device::PressKeyE() {
	return keys_[SDL_SCANCODE_E];
}

bool Device::PressKeyR() {
	return keys_[SDL_SCANCODE_R];
}

bool Device::PressKeyI() {
	return keys_[SDL_SCANCODE_I];
}

bool Device::PressKeyK() {
	return keys_[SDL_SCANCODE_K];
}

bool Device::PressKeyJ() {
	return keys_[SDL_SCANCODE_J];
}

bool Device::PressKeyL() {
	return keys_[SDL_SCANCODE_L];
}




} // namespace softrd
