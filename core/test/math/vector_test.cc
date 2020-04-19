#include "src/math/vector.h"

#include "absl/strings/str_format.h"
#include "gtest/gtest.h"

int main(int argc, char** argv) {
  softrd::vec3 v1(0, 1, 2);
  std::cout << v1.to_string() << std::endl;

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();

  return 0;
}