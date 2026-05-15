#include <iostream>
#include "math_utils.h"

int main() {
    int x = 6;
    int y = 7;

#ifdef USE_DOUBLE_VALUE
    x *= 2;
    y *= 2;
#endif

    std::cout << "add(" << x << ", " << y << ") = " << add(x, y) << '\n';
    std::cout << "multiply(" << x << ", " << y << ") = " << multiply(x, y) << '\n';
    std::cout << "subtract(" << x << ", " << y << ") = " << subtract(x, y) << '\n';

#ifdef ENABLE_VERBOSE_LOG
    std::cout << "[VERBOSE] lab1_app finished successfully." << '\n';
#endif

    return 0;
}
