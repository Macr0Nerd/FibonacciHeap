#pragma once

#ifndef GRON_FIBONACCI_HEAP_HPP
#define GRON_FIBONACCI_HEAP_HPP

#include <compare>
#include <concepts>
#include <map>
#include <memory>
#include <optional>
#include <ostream>
#include <vector>

template<std::three_way_comparable T>
class FibonacciHeap {
public:
    struct Node {
        T key;
        bool marked{};
        std::vector<Node*> children{};
        Node* parent{nullptr};

        explicit Node(T value) : key(value) {};

        Node(const Node&) = default;
        Node(Node&&) noexcept = default;
        Node& operator=(const Node&) = default;
        Node& operator=(Node&&) noexcept = default;
        virtual ~Node() = default;

        [[nodiscard]] size_t degree() const;
        [[nodiscard]] size_t size() const;

        bool operator==(const Node& obj) const;

        std::weak_ordering operator<=>(Node& obj) const;

        friend std::ostream& operator<<(std::ostream& os, const Node& obj) {
            return obj.streamInsertion(os);
        }

    private:
        std::ostream& streamInsertion(std::ostream& os) const;
    };

    std::vector<Node*> root_list;

    FibonacciHeap() = default;

    FibonacciHeap(const FibonacciHeap&) = default;
    FibonacciHeap(FibonacciHeap&&) noexcept = default;
    FibonacciHeap& operator=(const FibonacciHeap&) = default;
    FibonacciHeap& operator=(FibonacciHeap&&) noexcept = default;
    virtual ~FibonacciHeap() = default;

    [[nodiscard]] size_t size() const;

    void insert(const T& key);

    Node* get_minimum();
    std::optional<Node> pop_minimum();

    void alter_key(const T& key, const T& new_key);

    template<class Y> friend std::ostream& operator<<(std::ostream& os, const FibonacciHeap<Y>& obj);

protected:
    bool clean_flag{false};
    Node* minimum{nullptr};
    std::map<T, Node> location;

    void cut_key(Node& node, const T& key);
};

#include "GRon/FibonacciHeap/template/FibonacciHeap.tpp"
#endif //GRON_FIBONACCI_HEAP_HPP
