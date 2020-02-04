#include <iostream>

#include "src/renderer.h"

int main(int argc, char** argv)  // main entrance of this project
{
  softrd::Renderer renderer(640, 480);
  renderer.RunExample2();
  return 0;
}