#include <gtest/gtest.h>

#include "string_utils.h"

TEST(StringUtilsTest, Trim) {
    EXPECT_EQ(trim("  abc  "), "abc");
}

TEST(StringUtilsTest, SplitAndCount) {
    EXPECT_EQ(count_words("a,b,c", ','), 3u);
    EXPECT_EQ(split("x,,y", ',').size(), 2u);
}
