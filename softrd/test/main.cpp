#include <iostream>

#include "../src/renderer.h"

#include "../src/model.h"
#include "../src/device.h"

#include <SOIL/SOIL.h>
#include "../src/texture.h"

using namespace softrd;

int main()
{
	softrd::Renderer renderer(640, 480);
	renderer.Run();
	/*
	Device dev(100, 100, 800, 600);
	dev.Setup();
	while (true) {
		dev.DrawText("test");
	}
	*/



	return 0;
}