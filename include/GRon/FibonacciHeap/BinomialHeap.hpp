#pragma once

#ifndef GRON_BINOMIAL_HEAP_HPP
#define GRON_BINOMIAL_HEAP_HPP

#include <concepts>
#include <memory>
#include <optional>
#include <ostream>
#include <vector>

template<std::three_way_comparable T>
class BinomialHeap {
public:
    struct Node {
        std::vector<Node> children = {};
        T value;

        explicit Node(T value) : value(value), children() {};
        virtual ~Node() = default;

        [[nodiscard]] size_t degree() const;
        [[nodiscard]] size_t size() const;

        bool operator==(const Node& obj) const;

        std::weak_ordering operator<=>(Node obj) const;

        friend std::ostream& operator<<(std::ostream& os, const Node& obj) {
            return obj.streamInsertion(os);
        }

    private:
        std::ostream& streamInsertion(std::ostream& os) const;
    };

    std::vector<Node> root_list;

    BinomialHeap() = default;
    virtual ~BinomialHeap() = default;

    [[nodiscard]] size_t size() const;

    void insert(T value);

    std::optional<Node> get_minimum();
    std::optional<Node> pop_minimum();

    template<class Y> friend std::ostream& operator<<(std::ostream& os, const BinomialHeap<Y>& obj);

protected:
    bool clean_flag = false;
    std::optional<Node> minimum = std::nullopt;
};

#include "GRon/FibonacciHeap/template/BinomialHeap.tpp"
#endif //GRON_BINOMIAL_HEAP_HPP
