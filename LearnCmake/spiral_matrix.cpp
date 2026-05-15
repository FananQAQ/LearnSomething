#include <iomanip>
#include <iostream>
#include <vector>

static std::vector<std::vector<int>> make_spiral(int n) {
    std::vector<std::vector<int>> a(n, std::vector<int>(n, 0));
    int top = 0, bottom = n - 1, left = 0, right = n - 1;
    int v = 1;

    while (top <= bottom && left <= right) {
        for (int j = left; j <= right; ++j) a[top][j] = v++;
        ++top;

        for (int i = top; i <= bottom; ++i) a[i][right] = v++;
        --right;

        if (top <= bottom) {
            for (int j = right; j >= left; --j) a[bottom][j] = v++;
            --bottom;
        }

        if (left <= right) {
            for (int i = bottom; i >= top; --i) a[i][left] = v++;
            ++left;
        }
    }

    return a;
}

int main() {
    int n = 0;
    if (!(std::cin >> n) || n <= 0) return 0;

    auto m = make_spiral(n);
    int width = static_cast<int>(std::to_string(n * n).size()) + 1;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << std::setw(width) << m[i][j];
        }
        std::cout << '\n';
    }
    return 0;
}

