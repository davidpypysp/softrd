#include <iostream>

#include "../src/renderer.h"

#include "assimp/Importer.hpp"



int main()
{
	Assimp::Importer importer;
	softrd::Renderer renderer(640, 480);
	renderer.Run();
	return 0;
}