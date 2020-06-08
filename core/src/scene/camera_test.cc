#include "src/scene/camera.h"

#include <gtest/gtest.h>

using namespace softrd;

TEST(CameraTest, Genral) {
  scene::Camera camera(800.0 / 600.0);
  camera.direction();
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}