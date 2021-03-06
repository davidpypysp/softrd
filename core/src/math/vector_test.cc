#include "src/math/vector.h"

#include <gtest/gtest.h>

using namespace softrd;

TEST(VectorTest, Vector3) {
  math::vec3 v1(0, 1, 2);
  EXPECT_EQ(v1.ToString(), "(0.000000, 1.000000, 2.000000)");

  math::vec3 v2(0.0, 1.0, 2.0);
  EXPECT_EQ(v1, v2);

  math::vec3 v3 = v1 + v2;
  EXPECT_EQ(v3, math::vec3(0, 2, 4));

  EXPECT_EQ(v1.LengthSqr(), 5.0);
  EXPECT_FLOAT_EQ(v1.Length(), std::sqrt(5.0));
}

TEST(VectorTest, Vector4) {
  math::vec4 v1(0, 1, 2, 3);
  EXPECT_EQ(v1.ToString(), "(0.000000, 1.000000, 2.000000, 3.000000)");

  math::vec4 v2(0.0, 1.0, 2.0, 3);
  EXPECT_EQ(v1, v2);

  EXPECT_EQ(v1 - v2, math::vec4());
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}