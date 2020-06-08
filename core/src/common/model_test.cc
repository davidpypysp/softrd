#include "src/common/model.h"

#include <gtest/gtest.h>

using namespace softrd;

TEST(CameraTest, Genral) {
    Model model("/resource/suzanne/suzanne.blend");
}


int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}