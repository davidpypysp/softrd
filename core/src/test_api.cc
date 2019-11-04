#include <iostream>

#include "src/interface/renderer_api.h"

int main(int argc, char** argv)  // main entrance of this project
{
  softrd::RendererAPI renderer_api;
  renderer_api.ExamplePrint();
  return 0;
}