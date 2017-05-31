#include <iostream>

#include "../src/renderer.h"

#include "../src/model.h"
#include "../src/device.h"

#include <SOIL/SOIL.h>
#include "../src/texture.h"

using namespace softrd;

int main()
{
	mat3 a;
	mat3 b = a * 3.1;
	/*
	Texture texture("resource/img_cheryl.jpg");
	Device d(100, 100, texture.width, texture.height);
	d.Setup();
	while (true) {
		d.RenderClear();
		d.Draw(texture.fb);
		d.RenderPresent();
	}
	*/

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