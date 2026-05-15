#ifndef LAB2_STATS_H
#define LAB2_STATS_H

#if defined(_WIN32) && defined(LAB2_STATS_BUILD_DLL)
#define LAB2_STATS_API __declspec(dllexport)
#elif defined(_WIN32) && defined(LAB2_STATS_SHARED)
#define LAB2_STATS_API __declspec(dllimport)
#else
#define LAB2_STATS_API
#endif

#include <vector>

struct StatsSummary {
    int min_value;
    int max_value;
    double average;
};

LAB2_STATS_API StatsSummary summarize(const std::vector<int>& values);

#endif
