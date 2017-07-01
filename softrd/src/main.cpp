#include <iostream>

#include "renderer.h"

int main() // main entrance of this project
{
	softrd::Renderer renderer(640, 480);
	renderer.Run();
	return 0;
}