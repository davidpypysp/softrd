#include "src/common/model.h"

#include <gtest/gtest.h>

using namespace softrd;

TEST(CameraTest, Genral) {
    std::cout << "test model" << std::endl;
    Model model("abc");
}


int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}