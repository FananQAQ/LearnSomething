#include <gtest/gtest.h>

#include "stats.h"

TEST(StatsTest, Summarize) {
    const StatsSummary summary = summarize({2, 5, 9});
    EXPECT_EQ(summary.min_value, 2);
    EXPECT_EQ(summary.max_value, 9);
    EXPECT_DOUBLE_EQ(summary.average, 5.333333333333333);
}

TEST(StatsTest, EmptyInput) {
    const StatsSummary summary = summarize({});
    EXPECT_EQ(summary.min_value, 0);
    EXPECT_EQ(summary.max_value, 0);
    EXPECT_DOUBLE_EQ(summary.average, 0.0);
}
