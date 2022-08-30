#pragma once

#ifndef GRON_FIBONACCI_HEAP_HPP
#define GRON_FIBONACCI_HEAP_HPP

#include <compare>
#include <concepts>
#include <list>
#include <memory>
#include <optional>
#include <ostream>
#include <type_traits>

namespace GRon {
    template<std::three_way_comparable T,
            template<typename...> class Container = std::list,
            template<typename...> class Compare = std::less>
    class FibonacciHeap {
    public:
        struct Node {
        public:
            std::optional<T> key{std::nullopt};
            bool marked{false};
            Container<Node*> children{};
            Node* parent{nullptr};

            Node() = default;

            explicit Node(T value) : key(value) {};

            Node(const Node&) = default;

            Node(Node&&) noexcept = default;

            Node& operator=(const Node&) = default;

            Node& operator=(Node&&) noexcept = default;

            virtual ~Node() = default;

            [[nodiscard]] inline size_t degree() const noexcept;

            bool operator==(const Node& obj) const;

            bool operator==(const T &obj) const;

            std::weak_ordering operator<=>(Node& obj) const;

            std::weak_ordering operator<=>(T &obj) const;
        };

        Container<Node*> root_list;

        FibonacciHeap() = default;

        template<class... Args, typename = std::enable_if_t<(!std::is_base_of_v<FibonacciHeap, std::decay_t<Args>> && ...)>>
        explicit FibonacciHeap(Args&&... args) : _size(0), _clean(false), _top(nullptr),
                                                _nodes(std::forward<Args>(args)...), _removed(), root_list() {};

        FibonacciHeap(const FibonacciHeap&) = default;

        FibonacciHeap(FibonacciHeap&&) noexcept = default;

        FibonacciHeap& operator=(const FibonacciHeap&) = default;

        FibonacciHeap& operator=(FibonacciHeap&&) noexcept = default;

        virtual ~FibonacciHeap() = default;

        [[nodiscard]] inline size_t size() const noexcept;

        void insert(const T &key);

        Node* get_minimum();

        std::optional<Node> pop_minimum() &;
        std::optional<Node> pop_minimum() &&;

        void alter_key(const T &key, const T &new_key);

    protected:
        size_t _size{0};
        bool _clean{false};
        Node* _top{nullptr};
        Container<Node> _nodes;
        Container<Node*> _removed;

        void cut_key(Node* node, const T &key);
    };
}

#include "GRon/FibonacciHeap/template/FibonacciHeap.tpp"
#endif //GRON_FIBONACCI_HEAP_HPP
