////////////////////////////////////////////
////////////////////////////////////////////
////////////////////////////////////////////
//                            cpu_test.cpp
#include "gtest/gtest.h"

#include "test_includes.h"

//=========================================================================================
// Main, run all tests
int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}