#include "src/common/texture.h"

#include <gtest/gtest.h>

using namespace softrd;

TEST(TextureTest, Genral) { Texture texture("../../../resource/container.jpg"); }

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}