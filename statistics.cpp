#include "stats.h"
#include <iostream>

int main() {
    const size_t statistics_count = 4;
    stats::IStatistics *statistics[statistics_count];

    statistics[0] = new stats::Min{};
    statistics[1] = new stats::Max{};
    statistics[2] = new stats::Mean{};
    statistics[3] = new stats::STD{};

    double val = 0;
    while (true) {
        std::cin >> val;
        if (std::cin.eof()) {
            break;
        }
        if (std::cin.fail()) {
            std::cerr << "eof=" << std::cin.eof() << " fail=" << std::cin.fail()
                    << " bad=" << std::cin.bad() << "\n";
            break;
        }
        for (size_t i = 0; i < statistics_count; ++i) {
            statistics[i]->update(val);
        }
    }

    // Print results if any
    for (size_t i = 0; i < statistics_count; ++i) {
        std::cout << statistics[i]->name() << " = " << statistics[i]->eval()
                << std::endl;
    }

    // Clear memory - delete all objects created by new
    for (size_t i = 0; i < statistics_count; ++i) {
        delete statistics[i];
    }

    return 0;
}
