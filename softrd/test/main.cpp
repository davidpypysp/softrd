#include <iostream>

#include "../src/renderer.h"



int main()
{
	softrd::Renderer renderer(642, 480);
	renderer.Draw();
	return 0;
}