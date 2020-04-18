#include "src/math/vector.h"

#include <gtest/gtest.h>

int main(int argc, char** argv) {
  std::cout << "test" << std::endl;
  softrd::vec3 v1(0, 1, 2);
  v1.print();
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();

  return 0;
}