#include <iostream>
#include <vector>

#include "lab2/version.h"
#include "lab2_config.h"
#include "stats.h"
#include "string_utils.h"

int main() {
    std::cout << "lab2 version " << LAB2_VERSION_STRING << '\n';
    std::cout << "app: " << LAB2_APP_NAME << '\n';
    std::cout << "delimiter: '" << LAB2_DEFAULT_DELIMITER << "'\n";

    const std::string raw = "  hello,world,cmake  ";
    const std::string cleaned = trim(raw);
    const std::size_t words = count_words(raw, LAB2_DEFAULT_DELIMITER);

    std::cout << "raw text: \"" << raw << "\"\n";
    std::cout << "trimmed:    \"" << cleaned << "\"\n";
    std::cout << "word count: " << words << '\n';
    std::cout << "upper: \"" << to_upper(cleaned) << "\"\n";

    std::vector<int> samples{2, 5, 9};
#ifdef LAB2_ENABLE_DEMO_SCALE
    for (int& value : samples) {
        value *= 2;
    }
#endif

    std::cout << "samples:";
    for (int value : samples) {
        std::cout << ' ' << value;
    }
    std::cout << '\n';

    const StatsSummary summary = summarize(samples);
    std::cout << "stats -> min=" << summary.min_value
              << " max=" << summary.max_value
              << " avg=" << summary.average << '\n';

#ifdef LAB2_ENABLE_VERBOSE
    std::cout << "[VERBOSE] lab2_cli finished.\n";
#endif

    return 0;
}
