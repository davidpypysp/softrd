#include <iostream>

#include "../src/renderer.h"



int main()
{

	softrd::Renderer renderer(1280, 720);
	renderer.Run();
	return 0;
}