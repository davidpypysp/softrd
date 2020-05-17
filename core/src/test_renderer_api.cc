#include <iostream>

#include "src/interface/renderer_api.h"

int main() {
  std::cout << "test my renderer api" << std::endl;
  softrd::RendererAPI renderer_api;

  //   std::cout << "test texture api" << std::endl;
  softrd::Texture texture("something.jpg");

  return 1;
}