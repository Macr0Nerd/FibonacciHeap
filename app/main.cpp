#include <iostream>

#include "GRon/FibonacciHeap/BinomialHeap.hpp"

int main(int argc, char * argv[]) {
    BinomialHeap<int> test;

    test.insert(2);
    test.insert(3);
    test.insert(-1);
    test.insert(0);
    test.insert(6);

    test.get_minimum();

    std::cout << test << std::endl;

    std::cout << "Minimum: " << test.get_minimum().value().value << std::endl;

    return 0;
}
