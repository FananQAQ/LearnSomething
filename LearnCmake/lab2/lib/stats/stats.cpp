#include "stats.h"

#include <numeric>

StatsSummary summarize(const std::vector<int>& values) {
    StatsSummary result{0, 0, 0.0};
    if (values.empty()) {
        return result;
    }

    result.min_value = values.front();
    result.max_value = values.front();

    long long sum = 0;
    for (int value : values) {
        sum += value;
        if (value < result.min_value) {
            result.min_value = value;
        }
        if (value > result.max_value) {
            result.max_value = value;
        }
    }

    result.average = static_cast<double>(sum) / static_cast<double>(values.size());
    return result;
}
