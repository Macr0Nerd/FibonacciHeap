#pragma once

#ifndef GRON_BINOMIAL_HEAP_HPP
#define GRON_BINOMIAL_HEAP_HPP

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
    virtual ~FibonacciHeap() = default;

    [[nodiscard]] size_t size() const;

    void insert(const T& value);

    Node* get_minimum();
    Node* pop_minimum();

    void alter_key(const T& key, const T& new_key);

    template<class Y> friend std::ostream& operator<<(std::ostream& os, const FibonacciHeap<Y>& obj);

protected:
    bool clean_flag{false};
    Node* minimum{nullptr};
    std::map<T, Node> location;

    void cut_key(Node& node, const T& key);
};

#include "GRon/FibonacciHeap/template/FibonacciHeap.tpp"
#endif //GRON_BINOMIAL_HEAP_HPP
