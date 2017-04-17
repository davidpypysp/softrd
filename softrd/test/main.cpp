#include <iostream>

#include "../src/renderer.h"

#include "../src/model.h"


int main()
{
	softrd::Renderer renderer(800, 600);
	renderer.Run();
	return 0;
}