#include <catch2/catch_test_macros.hpp>
#include <GRon/FibonacciHeap/FibonacciHeap.hpp>

#include <algorithm>

TEST_CASE("heap basic functions", "[heap]") {
    GRon::FibonacciHeap<int> test;

    SECTION("init") {
        REQUIRE(test.size() == 0);
        REQUIRE_FALSE(test.get_minimum());
    }

    SECTION("insert") {
        test.insert(5);
        test.insert(-1);
        test.insert(0);
        test.insert(15);

        REQUIRE(test.size() == 4);
        auto iter = test.root_list.begin();

        REQUIRE((*iter)->key == 5);
        iter = std::next(iter);
        REQUIRE((*iter)->key.value() == -1);
        iter = std::next(iter);
        REQUIRE((*iter)->key.value() == 0);
        iter = std::next(iter);
        REQUIRE((*iter)->key.value() == 15);
        iter = std::next(iter);
    }

    SECTION("get_minimum") {
        test.insert(5);
        test.insert(-1);
        test.insert(0);
        test.insert(15);

        auto min = test.get_minimum();
        auto iter = min->children.begin();

        REQUIRE(min->key.value() == -1);
        REQUIRE((*iter)->key.value() == 5);
        iter = std::next(iter);
        REQUIRE((*iter)->children.front()->key.value() == 15);

        min = test.get_minimum();

        REQUIRE(min->key.value() == -1);

        SECTION("pop_minimum") {
            int min_key = min->key.value();
            GRon::FibonacciHeap<int>::Node pop_min = test.pop_minimum().value();

            REQUIRE(test.size() == 3);

            REQUIRE(pop_min.key.value() == min_key);

            REQUIRE(std::find(test.root_list.begin(), test.root_list.end(), min) == test.root_list.end());
        }

        min = test.get_minimum();
        iter = test.root_list.begin();

        REQUIRE(min->key.value() == 0);
        REQUIRE((*iter)->key.value()== 5);
        iter = std::next(iter);
        REQUIRE((*iter)->children.front()->key.value() == 15);
    }

    SECTION("alter_key") {
        test.insert(5);
        test.insert(-1);
        test.insert(0);
        test.insert(15);
        test.get_minimum();
        test.alter_key(15, -15);

        GRon::FibonacciHeap<int>::Node* min = test.get_minimum();

        REQUIRE(min->key == -15);

        test.insert(1);
        test.insert(2);
        test.insert(-4);
        test.insert(8);

        min = test.get_minimum();
        auto a = test.root_list;

        auto iter = test.root_list.begin();

        REQUIRE(test.size() == 8);
        REQUIRE(min->key.value() == -15);
        REQUIRE((*iter)->key.value() == 8);
        iter = std::next(iter, 3);
        REQUIRE((*iter)->key.value() == -15);

        iter = std::next((*iter)->children.begin());
        REQUIRE((*iter)->key.value() == -4);
        iter = std::next((*std::next(iter))->children.begin());
        REQUIRE((*iter)->key.value() == 0);
    }
}