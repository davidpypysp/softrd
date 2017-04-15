#include <iostream>

#include "../src/renderer.h"



int main()
{
	softrd::Renderer renderer(640, 480);
	renderer.Run();
	return 0;
}