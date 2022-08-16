#include <catch2/catch_test_macros.hpp>
#include <GRon/FibonacciHeap/FibonacciHeap.hpp>

#include <algorithm>

TEST_CASE("heap basic functions", "[heap]") {
    FibonacciHeap<int> test{};

    SECTION("init") {
        REQUIRE(test.size() == 0);
        REQUIRE(test.get_minimum() == nullptr);
    }

    SECTION("insert") {
        test.insert(5);
        test.insert(-1);
        test.insert(0);
        test.insert(15);

        REQUIRE(test.size() == 4);

        REQUIRE(test.root_list.at(0)->key == 5);
        REQUIRE(test.root_list.at(1)->key == -1);
        REQUIRE(test.root_list.at(2)->key == 0);
        REQUIRE(test.root_list.at(3)->key == 15);
    }

    SECTION("get_minimum") {
        test.insert(5);
        test.insert(-1);
        test.insert(0);
        test.insert(15);

        FibonacciHeap<int>::Node* min = test.get_minimum();

        REQUIRE(min->key == -1);
        REQUIRE(min->children.at(0)->key == 5);
        REQUIRE(min->children.at(1)->children.at(0)->key == 15);

        min = test.get_minimum();

        REQUIRE(min->key == -1);

        SECTION("pop_minimum") {
            int min_key = min->key;
            FibonacciHeap<int>::Node pop_min = test.pop_minimum().value();

            REQUIRE(test.size() == 3);

            REQUIRE(pop_min.key == min_key);

            REQUIRE(std::find(test.root_list.begin(), test.root_list.end(), min) == test.root_list.end());
        }

        min = test.get_minimum();

        REQUIRE(min->key == 0);
        REQUIRE(test.root_list.at(0)->key == 5);
        REQUIRE(test.root_list.at(1)->children.at(0)->key == 15);
    }

    SECTION("alter_key") {
        test.insert(5);
        test.insert(-1);
        test.insert(0);
        test.insert(15);
        test.get_minimum();
        test.alter_key(15, -15);

        FibonacciHeap<int>::Node* min = test.get_minimum();

        REQUIRE(min->key == -15);

        test.insert(1);
        test.insert(2);
        test.insert(-4);
        test.insert(8);

        min = test.get_minimum();

        REQUIRE(test.size() == 8);
        REQUIRE(min->key == -15);
        REQUIRE(test.root_list.at(0)->key == 8);
        REQUIRE(test.root_list.at(1)->key == -15);
        REQUIRE(test.root_list.at(1)->children.at(1)->key == -4);
        REQUIRE(test.root_list.at(1)->children.at(2)->children.at(1)->key == 0);
    }
}