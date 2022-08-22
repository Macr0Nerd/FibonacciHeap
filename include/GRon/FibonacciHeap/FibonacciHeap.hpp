#pragma once

#ifndef GRON_FIBONACCI_HEAP_HPP
#define GRON_FIBONACCI_HEAP_HPP

#include <compare>
#include <concepts>
#include <list>
#include <memory>
#include <optional>
#include <ostream>

namespace GRon {
    template<std::three_way_comparable T, template<typename...> class Container = std::list>
    class FibonacciHeap {
    public:
        struct Node {
            std::optional<T> key{std::nullopt};
            bool marked{false};
            Container<Node *> children{};
            Node *parent{nullptr};

            Node() = default;

            explicit Node(T value) : key(value) {};

            Node(const Node &) = default;

            Node(Node &&) noexcept = default;

            Node &operator=(const Node &) = default;

            Node &operator=(Node &&) noexcept = default;

            virtual ~Node() = default;

            [[nodiscard]] size_t degree() const;

            [[nodiscard]] size_t size() const;

            bool operator==(const Node &obj) const;

            bool operator==(const T &obj) const;

            std::weak_ordering operator<=>(Node &obj) const;

            std::weak_ordering operator<=>(T &obj) const;
        };

        Container<Node *> root_list;

        FibonacciHeap() = default;

        explicit FibonacciHeap(size_t reserve) : _size(0), _clean(false), _minimum(nullptr), _nodes(reserve),
                                                 _removed(), root_list() {};

        FibonacciHeap(const FibonacciHeap &) = default;

        FibonacciHeap(FibonacciHeap &&) noexcept = default;

        FibonacciHeap &operator=(const FibonacciHeap &) = default;

        FibonacciHeap &operator=(FibonacciHeap &&) noexcept = default;

        virtual ~FibonacciHeap() = default;

        [[nodiscard]] size_t size() const;

        void insert(const T &key);

        Node *get_minimum();

        std::optional<Node> pop_minimum();

        void alter_key(const T &key, const T &new_key);

    protected:
        size_t _size{0};
        bool _clean{false};
        Node *_minimum{nullptr};
        Container<Node> _nodes;
        Container<Node *> _removed;

        void cut_key(Node *node, const T &key);
    };
}

#include "GRon/FibonacciHeap/template/FibonacciHeap.tpp"
#endif //GRON_FIBONACCI_HEAP_HPP
