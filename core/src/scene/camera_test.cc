#include "src/scene/camera.h"

#include <glog/logging.h>
#include <gtest/gtest.h>

using namespace softrd;

TEST(CameraTest, Genral) {
  scene::Camera camera(800.0 / 600.0);
  camera.direction();
  LOG(INFO) << "camera.direction: " << camera.direction().ToString();
}

int main(int argc, char** argv) {
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  testing::InitGoogleTest(&argc, argv);
  google::InitGoogleLogging(argv[0]);

  return RUN_ALL_TESTS();
}