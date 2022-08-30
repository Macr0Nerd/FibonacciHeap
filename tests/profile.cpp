#include "GRon/FibonacciHeap/FibonacciHeap.hpp"

#include <iostream>

int main() {
    int n = 100000;
    int ratio = 512;
    bool invert = false;

    int one = n/100;

    std::cout << "n=" << n << ", ratio=" << ratio << ", invert=" << invert << std::endl;
    std::cout << "=======================================================" << std::endl;

    int pop_cnt = 0, insert_cnt = 0;

    GRon::FibonacciHeap<int> test = GRon::FibonacciHeap<int>(static_cast<size_t>(n));
    for (int i = 0; i < n; i++) {
        if (!(i % one)) {
            std::cout << '\r' << (i/(double) n) * 100 << "% Complete" << std::flush;
        }

        if (!(i % ratio)) {
            test.get_minimum();
            pop_cnt++;
            continue;
        }

        test.insert(i);
        insert_cnt++;
    }

    std::cout << '\r' << 100 << "% Complete" << std::flush;

    std::cout << std::endl;
    std::cout << "Results" << std::endl;
    std::cout << "==============" << std::endl;
    std::cout << "Get: " << pop_cnt << " ops" << std::endl;
    std::cout << "Insert: " << insert_cnt << " ops" << std::endl;

    return 0;
}
