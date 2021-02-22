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

TEST(RegularTest, SimpleNoSubstitution){
  auto str = fp::format("The cake is a lie!");
  EXPECT_EQ(str, "The cake is a lie!");
}

TEST(RegularTest, SubstitutionWithPercentI){
  auto str = fp::format("The answer is always %i.", 42);
  EXPECT_EQ(str, "The answer is always 42.");
}

TEST(RegularTest, SubstitutionWithPercentD){
  auto str = fp::format("For instance : 1 + 1 = %d", 42);
  EXPECT_EQ(str, "For instance : 1 + 1 = 42");
}

TEST(RegularTest, SubstitutionWithPercentF){
  auto str = fp::format("But what about floats? It's %f, easy.", 42.424242);
  EXPECT_EQ(str, "But what about floats? It's 42.424242, easy.");
}

TEST(RegularTest, SubstitutionWithPercentB){
  auto str = fp::format("Which means, 5*5 = 25 is %b, and 5*5 = 42 is %b", false, true);
  EXPECT_EQ(str, "Which means, 5*5 = 25 is false, and 5*5 = 42 is true");
}

TEST(RegularTest, SubstitutionWithPercentC){
  auto str = fp::format("Is someone says otherwise, just say %c%c", 'n', 'o');
  EXPECT_EQ(str, "Is someone says otherwise, just say no");
}

TEST(RegularTest, SubstitutionWithPercentP){
  int variable = 42;
  const int *ptr = &variable;
  auto str = fp::format("Also I just made a variable with the number 42 in it, it's address is %p", &variable);
  auto str_test = "Also I just made a variable with the number 42 in it, it's address is " + *ptr;
  EXPECT_EQ(str, str_test);
}

TEST(RegularTest, SubstitutionWithPercentPNullptr){
  auto str = fp::format("Which is not the same as a nullptr, which has the adress %p", nullptr);
  EXPECT_EQ(str, "Which is not the same as a nullptr, which has the adress 0x0");
}

TEST(RegularTest, SubstitutionWithPercentX){
  auto str = fp::format("By the way, did you know that the hexadecimal representation of 42 is %x", 42);
  EXPECT_EQ(str, "By the way, did you know that the hexadecimal representation of 42 is 0x2A");
}


int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
