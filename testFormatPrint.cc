#include <gtest/gtest.h>

#include "Format.h"

namespace my {
  struct Foo {
    int i;
  };

  std::string to_string(const Foo& foo) {
    return std::to_string(foo.i);
  }
}

TEST(EasyTest, SimpleNoChange){
  auto str = fp::format("The cake is a lie!");
  EXPECT_EQ(str, "The cake is a lie!");
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
