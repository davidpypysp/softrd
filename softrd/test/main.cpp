#include <iostream>

#include "../src/renderer.h"



int main()
{
	int cnt = 0;
	for (int i = 0; i < 1640; i++) {
		for (int j = 0; j < 1480; j++) {
			cnt++;
		}
	}
	softrd::Renderer renderer(640, 480);
	renderer.Draw();
	return 0;
}