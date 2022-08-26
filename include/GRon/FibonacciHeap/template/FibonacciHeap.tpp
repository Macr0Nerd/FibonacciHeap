#include "GRon/FibonacciHeap/FibonacciHeap.hpp"

#include <algorithm>
#include <array>
#include <cmath>
#include <vector>

/// Node
template<std::three_way_comparable T, template<typename...> class Container, template<typename...> class Compare>
size_t GRon::FibonacciHeap<T, Container, Compare>::Node::degree() const noexcept {
    return children.size();
}

template<std::three_way_comparable T, template<typename...> class Container, template<typename...> class Compare>
bool GRon::FibonacciHeap<T, Container, Compare>::Node::operator==(const FibonacciHeap::Node& obj) const {
    return key == obj.key;
}

template<std::three_way_comparable T, template<typename...> class Container, template<typename...> class Compare>
bool GRon::FibonacciHeap<T, Container, Compare>::Node::operator==(const T& obj) const {
    return key == obj;
}

template<std::three_way_comparable T, template<typename...> class Container, template<typename...> class Compare>
std::weak_ordering GRon::FibonacciHeap<T, Container, Compare>::Node::operator<=>(Node& obj) const {
    return key <=> obj.key;
}

template<std::three_way_comparable T, template<typename...> class Container, template<typename...> class Compare>
std::weak_ordering GRon::FibonacciHeap<T, Container, Compare>::Node::operator<=>(T& obj) const {
    return key <=> obj;
}

/// Fibonacci Heap
template<std::three_way_comparable T, template<typename...> class Container, template<typename...> class Compare>
size_t GRon::FibonacciHeap<T, Container, Compare>::size() const noexcept {
    return _size;
}

template<std::three_way_comparable T, template<typename...> class Container, template<typename...> class Compare>
void GRon::FibonacciHeap<T, Container, Compare>::insert(const T& key) {
    _clean = true;
    _size++;

    if (_removed.empty()) {
        root_list.push_back(&_nodes.emplace_back(key));
        return;
    }

    *_removed.back() = Node(key);
    root_list.push_back(_removed.back());
    _removed.pop_back();
}

template<std::three_way_comparable T, template<typename...> class Container, template<typename...> class Compare>
typename GRon::FibonacciHeap<T, Container, Compare>::Node* GRon::FibonacciHeap<T, Container, Compare>::get_minimum() {
    if (_clean) {
        std::optional<size_t> max_degree = std::nullopt;

        max_degree = std::log2f((double) size()) * 1.618;

        if (!max_degree.has_value()) return nullptr;

        Container<Node*> degree_list(max_degree.value(), nullptr);

        Node* current{nullptr};
        Node* node{nullptr};
        Compare<T> compare{};
        auto start = degree_list.begin();
        for (Node* root : root_list) {
            if (!root) continue;

            size_t degree = root->degree();
            current = *std::next(start, degree);
            if (!current) {
                *std::next(start, degree) = root;
                continue;
            }

            node = root;
            while (current) {
                if (compare(node->key.value(), current->key.value())) {
                    current->parent = node;
                    node->children.push_back(current);
                } else {
                    node->parent = current;
                    current->children.push_back(node);
                    node = current;
                }

                *std::next(start, degree) = nullptr;

                if (degree + 1 >= degree_list.size()) break;

                degree = node->degree();
                current = *std::next(start, degree);
            }

            *std::next(start, degree) = node;
        }

        /// This can be moved into the main loop above to improve efficiency for easily compared types,
        /// but the partial specialization necessary is impossible, and making a base class has proven to be very very
        /// frustrating.
        _top = nullptr;
        root_list.swap(degree_list);
        for (auto& i : root_list) {
            if (i && (!_top || compare(i->key.value(), _top->key.value()))) {
                _top = i;
            }
        }

        _clean = false;
    }

    return _top;
}

template<std::three_way_comparable T, template<typename...> class Container, template<typename...> class Compare>
std::optional<typename GRon::FibonacciHeap<T, Container, Compare>::Node> GRon::FibonacciHeap<T, Container, Compare>::pop_minimum() & {
    Node* min = get_minimum();

    if (!min) return std::nullopt;

    for (Node* node : min->children) {
        node->parent = nullptr;
    }

    root_list.insert(root_list.end(), min->children.begin(), min->children.end());
    std::erase(root_list, min);

    _removed.push_back(min);

    _top = nullptr;
    _clean = true;
    _size--;

    return *min;
}

template<std::three_way_comparable T, template<typename...> class Container, template<typename...> class Compare>
std::optional<typename GRon::FibonacciHeap<T, Container, Compare>::Node> GRon::FibonacciHeap<T, Container, Compare>::pop_minimum() && {
    const Node* min = get_minimum();

    if (!min) return std::nullopt;

    for (Node* node : min->children) {
        node->parent = nullptr;
    }

    root_list.insert(root_list.end(), min->children.begin(), min->children.end());
    std::erase(root_list, min);

    _removed.push_back(&(*std::find(_nodes.begin(), _nodes.end(), *min)));

    _top = nullptr;
    _clean = true;
    _size--;

    return std::move(*min);
}

template<std::three_way_comparable T, template<typename...> class Container, template<typename...> class Compare>
void GRon::FibonacciHeap<T, Container, Compare>::cut_key(FibonacciHeap::Node* node, const T& key) {
    if (!node) return;

    _clean = true;

    node->key = key;
    node->marked = false;
    Node* old_parent = node->parent;
    node->parent = nullptr;

    root_list.push_back(node);

    if (old_parent) {
        old_parent->children.erase(std::remove(old_parent->children.begin(), old_parent->children.end(), node));

        if (!old_parent->marked) {
            old_parent->marked = true;
        } else {
            cut_key(old_parent, old_parent->key.value());
        }
    }
}

template<std::three_way_comparable T, template<typename...> class Container, template<typename...> class Compare>
void GRon::FibonacciHeap<T, Container, Compare>::alter_key(const T& key, const T& new_key) {
    auto old = std::find(_nodes.begin(), _nodes.end(), key);
    if (old == _nodes.end()) return;

    cut_key(&(*old), new_key);
}