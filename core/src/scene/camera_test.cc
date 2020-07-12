#include "src/scene/camera.h"

#include <gtest/gtest.h>

using namespace softrd;

TEST(CameraTest, Genral) {
  scene::Camera camera(math::vec3(6.0, 6.0, 10.0), 800.0 / 600.0);
  camera.direction();
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}