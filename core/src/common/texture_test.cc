#include "src/common/texture.h"

#include <glog/logging.h>
#include <gtest/gtest.h>

#include <experimental/filesystem>

using namespace softrd;
namespace fs = std::experimental::filesystem;

TEST(CameraTest, Genral) {
  LOG(INFO) << "Current path: " << fs::current_path();
  Texture texture("../../../resource/container.jpg");
}

int main(int argc, char** argv) {
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  testing::InitGoogleTest(&argc, argv);
  google::InitGoogleLogging(argv[0]);

  return RUN_ALL_TESTS();
}