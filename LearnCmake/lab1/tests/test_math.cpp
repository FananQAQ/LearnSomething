#include "math_utils.h"
#include <gtest/gtest.h>

TEST(MathUtilsTest, Add) {
    EXPECT_EQ(add(1, 2), 3);    
}

TEST(MathUtilsTest, Multiply) {
    EXPECT_EQ(multiply(2, 3), 6);
}

TEST(MathUtilsTest, Subtract) {
    EXPECT_EQ(subtract(5, 3), 2);
}