#include <iostream>

#include "../src/renderer.h"

#include "../src/model.h"


int main()
{
	softrd::Renderer renderer(1280, 720);
	renderer.Run();
	return 0;
}