#include <limits.h>
#include "gtest/gtest.h"
#include "odd.h"

// Tests factorial of 0.
TEST(FactorialTest3, Zero) {
  EXPECT_EQ(false, odd(0));
}

// Tests factorial of positive numbers.
TEST(FactorialTest3, Positive) {
  EXPECT_EQ(true, odd(1));
  EXPECT_EQ(false, odd(2));
  EXPECT_EQ(false, odd(4));
}
