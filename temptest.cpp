#include <iostream>
#include <vector>

int main() {
    std::vector<std::vector<double>> Xx = {{152, 135, 165, 175, 136},
                                           {230, 234, 231, 260, 125},
                                           {231, 204, 235, 240, 135}};

    std::vector<double> columnSums(Xx[0].size(), 0.0);

    // Sum each column
    for (const auto& row : Xx) {
        for (size_t i = 0; i < row.size(); ++i) {
            columnSums[i] += row[i];
        }
    }

    // Print column sums
    std::cout << "Column sums: ";
    for (double sum : columnSums) {
        std::cout << sum << " ";
    }
    std::cout << std::endl;

    return 0;
}
