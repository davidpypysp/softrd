#include "src/common/texture.h"

#include <gtest/gtest.h>

using namespace softrd;

TEST(CameraTest, Genral) { Texture texture("../../../resource/container.jpg"); }

int main(int argc, char** argv) {
  // gflags::ParseCommandLineFlags(&argc, &argv, true);
  testing::InitGoogleTest(&argc, argv);
  // google::InitGoogleLogging(argv[0]);

  return RUN_ALL_TESTS();
}