#include <iostream>

#include "../src/renderer.h"



int main()
{
	softrd::Renderer renderer(1640, 800);
	renderer.Draw();
	return 0;
}