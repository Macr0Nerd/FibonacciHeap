#include <iostream>

#include "GRon/FibonacciHeap/FibonacciHeap.hpp"

int main(int argc, char * argv[]) {
    FibonacciHeap<int> test;

    test.insert(3);
    test.insert(4);
    test.insert(-1);
    test.insert(0);
    test.insert(6);

    test.get_minimum();

    std::cout << test << std::endl;

    auto x = test.get_minimum();
    std::cout << "Minimum: " << x->key << std::endl << std::endl;

    test.alter_key(4, 2);
    test.get_minimum();

    std::cout << test << std::endl;
    std::cout << "Minimum: " << x->key << std::endl;

    return 0;
}
