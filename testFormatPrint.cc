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

  std::ostringstream get_the_address; 
  get_the_address << &foo;
  std::string address =  get_the_address.str(); 
  
  str = fp::format("%p", &foo);
  EXPECT_EQ(str, address);
  
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

TEST(RegularTest, alonePercent)
{
  bool test = false;
  try
  {
    auto str = fp::format("This will fail %");
  }
  catch(const std::exception& e)
  {
    test = true;
  }
  EXPECT_TRUE(test);
}

TEST(RegularTest, SubstitutionWithMultiplePercents){
  auto str = fp::format("If you want to print 42 on a computer, you need to use %%i or %%d");
  EXPECT_EQ(str, "If you want to print 42 on a computer, you need to use %i or %d");
}

TEST(RegularTest, SubstitutionWithMultiplePercentsTheSequel){
  auto str = fp::format("But be careful not to use %%%i or %%%d, you just need one %%", 42, 42);
  EXPECT_EQ(str, "But be careful not to use %42 or %42, you just need one %");
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
  int res = 42;
  auto str = fp::format("Test : %i", res);
  EXPECT_EQ(str, "Test : 42");
}

TEST(PercentI, goodLong)
{
  long res = 42;
  auto str = fp::format("Test : %i", res);
  EXPECT_EQ(str, "Test : 42");
}

TEST(PercentI, goodConst)
{
  const int res = 42;
  auto str = fp::format("Test : %i", res);
  EXPECT_EQ(str, "Test : 42");
}

TEST(PercentI, goodSigned)
{
  signed int res = -42;
  auto str = fp::format("Test : %i", res);
  EXPECT_EQ(str, "Test : -42");
}

TEST(PercentI, goodUnsigned)
{
  unsigned int res = 42;
  auto str = fp::format("Test : %i", res);
  EXPECT_EQ(str, "Test : 42");
}

TEST(PercentI, goodPointer)
{
  int* res = new int(42);
  auto str = fp::format("Test : %i", *res);
  EXPECT_EQ(str, "Test : 42");
  delete(res);
}

TEST(PercentI, noValue)
{
  bool test = false;
  try
  {
    auto str = fp::format("Test : %i");
  }
  catch(const std::exception& e)
  {
    test = true;
  }
  EXPECT_TRUE(test);
}

TEST(PercentI, tooManyValues)
{
  bool test = false;
  try
  {
    auto str = fp::format("Test : %i", 42, 24);
  }
  catch(const std::exception& e)
  {
    test = true;
  }
  EXPECT_TRUE(test);
}

TEST(PercentI, badFormat)
{
  bool test = false;
  try
  {
    auto str = fp::format("Test : %i", 42.424242);
  }
  catch(const std::exception& e)
  {
    test = true;
  }
  EXPECT_TRUE(test);
}

TEST(PercentI, nullPtr)
{
  bool test = false;
  try
  {
    auto str = fp::format("Test : %i", nullptr);
  }
  catch(const std::exception& e)
  {
    test = true;
  }
  EXPECT_TRUE(test);
}

TEST(PercentD, goodInt)
{
  int res = 42;
  auto str = fp::format("Test : %d", res);
  EXPECT_EQ(str, "Test : 42");
}

TEST(PercentD, goodLong)
{
  long res = 42;
  auto str = fp::format("Test : %d", res);
  EXPECT_EQ(str, "Test : 42");
}

TEST(PercentD, goodConst)
{
  const int res = 42;
  auto str = fp::format("Test : %d", res);
  EXPECT_EQ(str, "Test : 42");
}

TEST(PercentD, goodSigned)
{
  signed int res = -42;
  auto str = fp::format("Test : %d", res);
  EXPECT_EQ(str, "Test : -42");
}

TEST(PercentD, goodUnsigned)
{
  unsigned int res = 42;
  auto str = fp::format("Test : %d", res);
  EXPECT_EQ(str, "Test : 42");
}

TEST(PercentD, goodPointer)
{
  int *res = new int(42);
  auto str = fp::format("Test : %d", *res);
  EXPECT_EQ(str, "Test : 42");
  delete(res);
}

TEST(PercentD, noValue)
{
  bool test = false;
  try
  {
    auto str = fp::format("Test : %d");
  }
  catch(const std::exception& e)
  {
    test = true;
  }
  EXPECT_TRUE(test);
}

TEST(PercentD, tooManyValues)
{
  bool test = false;
  try
  {
    auto str = fp::format("Test : %d", 42, 24);
  }
  catch(const std::exception& e)
  {
    test = true;
  }
  EXPECT_TRUE(test);
}

TEST(PercentD, badFormat)
{
  bool test = false;
  try
  {
    auto str = fp::format("Test : %d", 42.424242);
  }
  catch(const std::exception& e)
  {
    test = true;
  }
  EXPECT_TRUE(test);
}

TEST(PercentD, nullPtr)
{
  bool test = false;
  try
  {
    auto str = fp::format("Test : %d", nullptr);
  }
  catch(const std::exception& e)
  {
    test = true;
  }
  EXPECT_TRUE(test);
}

/*TEST(PercentF, goodFloat)
{
  float res = 42.424242;
  auto str = fp::format("Test : %f", res);
  EXPECT_EQ(str, "Test : 42.424242");
}

TEST(PercentF, goodPointer)
{
  float *res = new float(42.424242);
  auto str = fp::format("Test : %f", *res);
  EXPECT_EQ(str, "Test : 42.424242");
  delete(res);
}*/

TEST(PercentF, noValue)
{
  bool test = false;
  try
  {
    auto str = fp::format("Test : %f");
  }
  catch(const std::exception& e)
  {
    test = true;
  }
  EXPECT_TRUE(test);
}

TEST(PercentF, tooManyValues)
{
  bool test = false;
  try
  {
    auto str = fp::format("Test : %f", 42.424242, 24.242424 );
  }
  catch(const std::exception& e)
  {
    test = true;
  }
  EXPECT_TRUE(test);
}

TEST(PercentF, badFormat1)
{
  bool test = false;
  try
  {
    auto str = fp::format("Test : %f", true);
  }
  catch(const std::exception& e)
  {
    test = true;
  }
  EXPECT_TRUE(test);
}

TEST(PercentF, badFormat2)
{
  bool test = false;
  try
  {
    auto str = fp::format("Test : %f", true);
  }
  catch(const std::exception& e)
  {
    test = true;
  }
  EXPECT_TRUE(test);
}

TEST(PercentF, nullPtr)
{
  bool test = false;
  try
  {
    auto str = fp::format("Test : %f", nullptr);
  }
  catch(const std::exception& e)
  {
    test = true;
  }
  EXPECT_TRUE(test);
}

TEST(PercentB, goodBool)
{
  bool res = true;
  auto str = fp::format("Test : %b", res);
  EXPECT_EQ(str, "Test : true");
}

TEST(PercentB, goodPointer)
{
  bool *res = new bool(true);
  auto str = fp::format("Test : %b", *res);
  EXPECT_EQ(str, "Test : true");
  delete(res);
}

TEST(PercentB, noValue)
{
  bool test = false;
  try
  {
    auto str = fp::format("Test : %b");
  }
  catch(const std::exception& e)
  {
    test = true;
  }
  EXPECT_TRUE(test);
}

TEST(PercentB, tooManyValues)
{
  bool test = false;
  try
  {
    auto str = fp::format("Test : %b", true, false);
  }
  catch(const std::exception& e)
  {
    test = true;
  }
  EXPECT_TRUE(test);
}

TEST(PercentB, badFormat)
{
  bool test = false;
  try
  {
    auto str = fp::format("Test : %b", 42);
  }
  catch(const std::exception& e)
  {
    test = true;
  }
  EXPECT_TRUE(test);
}

TEST(PercentB, nullPtr)
{
  bool test = false;
  try
  {
    auto str = fp::format("Test : %b", nullptr);
  }
  catch(const std::exception& e)
  {
    test = true;
  }
  EXPECT_TRUE(test);
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
