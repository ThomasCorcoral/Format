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

TEST(SubjectExample, Test)
{
  auto str = fp::format("%s %s!", "Hello", "World");
  EXPECT_EQ(str, "Hello World!");
  
  str = fp::format("The  cake is a lie!");
  EXPECT_EQ(str, "The  cake is a lie!");
  
  str = fp::format("The  Answer is %d", 42);
  EXPECT_EQ(str, "The  Answer is 42");
  
  str = fp::format("Approximation of %s is %f", "Pi", 3.141592);
  EXPECT_EQ(str, "Approximation of Pi is 3.141592");
  
  str = fp::format("%d in  hexadecimal %x", 42, 42);
  EXPECT_EQ(str, "42 in  hexadecimal 0x2a");
  
  str = fp::format("'%c' is the 1st alphabet letter", 'A');
  EXPECT_EQ(str, "'A' is the 1st alphabet letter");
  
  str = fp::format("This  sentence  is %b",false);
  EXPECT_EQ(str, "This  sentence  is false");
  
  my::Foo  foo = { 8 };
  str = fp::format("%o", foo);
  EXPECT_EQ(str, "8");
  
  str = fp::format("%p", &foo);
  EXPECT_EQ(str, "0x");
  
  str = fp::format("No  substitution: %%i");
  EXPECT_EQ(str, "No  substitution: %i");
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
  int *variable = new int(42);
  std::ostringstream get_the_address; 
  get_the_address << variable;
  std::string address =  get_the_address.str(); 
  auto str = fp::format("Also I just made a variable with the number 42 in it, it's address is %p", variable);
  auto str_test = "Also I just made a variable with the number 42 in it, it's address is " + address;
  EXPECT_EQ(str, str_test);
  delete(variable);
}

TEST(RegularTest, SubstitutionWithPercentPNullptr){
  auto str = fp::format("Which is not the same as a nullptr, which has the adress %p", nullptr);
  EXPECT_EQ(str, "Which is not the same as a nullptr, which has the adress 0x0");
}

TEST(RegularTest, SubstitutionWithPercentX){
  auto str = fp::format("By the way, did you know that the hexadecimal representation of 42 is %x", 42);
  EXPECT_EQ(str, "By the way, did you know that the hexadecimal representation of 42 is 0x2a");
}

TEST(RegularTest, SubstitutionWithPercentS){
  auto str = fp::format("So yeah, 42 is the universal %s", "answer");
  EXPECT_EQ(str, "So yeah, 42 is the universal answer");
}

TEST(RegularTest, SubstitutionWithMultiplePercents){
  auto str = fp::format("If you want to print 42 on a computer, you need to use %%i or %%d");
  EXPECT_EQ(str, "If you want to print 42 on a computer, you need to use %i or %d");
}
TEST(RegularTest, SubstitutionWithMultiplePercentsTheSequel){
  auto str = fp::format("But be careful not to use %%%i or %%%d, you just need one %");
  EXPECT_EQ(str, "But be careful not to use %%i or %%d, you just need one %");
}

TEST(RegularTest, MultipleSubstitutions){
  auto str = fp::format("So in the end, when someone asks you %s the time, you just say %d, or %f or %x", "for", 42, 42.424242, 42);
  EXPECT_EQ(str, "So in the end, when someone asks you for the time, you just say 42, or 42.424242 or 0x2a");
}

TEST(RegularTest, MultipleSubstitutions2){
  std::string input_str = "for";
  auto str = fp::format("So in the end, when someone asks you %s the time, you just say %d, or %f or %x", input_str, 42, 42.424242, 42);
  EXPECT_EQ(str, "So in the end, when someone asks you for the time, you just say 42, or 42.424242 or 0x2a");
}

TEST(RegularTest, MultipleSubstitutions3){
  const char* input_str = "for";
  auto str = fp::format("So in the end, when someone asks you %s the time, you just say %d, or %f or %x", input_str, 42, 42.424242, 42);
  EXPECT_EQ(str, "So in the end, when someone asks you for the time, you just say 42, or 42.424242 or 0x2a");
}

TEST(RegularTest, MultipleSubstitutionsWithMultiplePercents){
  auto str = fp::format("So in the end, when someone asks you %s the time, you just say %d with %%i or %%d, %f with %%f or %x with %%x", "for", 42, 42.424242, 42);
  EXPECT_EQ(str, "So in the end, when someone asks you for the time, you just say 42 with %i or %d, 42.424242 with %f or 0x2a with %x");
}

TEST(PercentI, goodInt)
{

}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
