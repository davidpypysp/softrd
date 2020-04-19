#include "src/math/vector.h"

#include <gtest/gtest.h>

#include "absl/strings/str_format.h"

int main(int argc, char** argv) {
  std::cout << "test" << std::endl;
  softrd::vec3 v1(0, 1, 2);
  v1.print();

  std::string s = absl::StrFormat("abc %d", 10);
  std::cout << s << std::endl;

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();

  return 0;
}