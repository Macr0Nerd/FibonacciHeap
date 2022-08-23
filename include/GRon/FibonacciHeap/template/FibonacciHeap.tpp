#include "GRon/FibonacciHeap/FibonacciHeap.hpp"

#include <algorithm>
#include <array>
#include <cmath>
#include <vector>

/// Node
template<std::three_way_comparable T, template<typename...> class Container>
size_t GRon::FibonacciHeap<T, Container>::Node::degree() const {
    return children.size();
}

template<std::three_way_comparable T, template<typename...> class Container>
size_t GRon::FibonacciHeap<T, Container>::Node::size() const {
    size_t ret = 1;

    for (auto& i : children) {
        ret += i->size();
    }

    return ret;
}

template<std::three_way_comparable T, template<typename...> class Container>
bool GRon::FibonacciHeap<T, Container>::Node::operator==(const FibonacciHeap::Node& obj) const {
    return key == obj.key;
}

template<std::three_way_comparable T, template<typename...> class Container>
bool GRon::FibonacciHeap<T, Container>::Node::operator==(const T& obj) const {
    return key == obj;
}

template<std::three_way_comparable T, template<typename...> class Container>
std::weak_ordering GRon::FibonacciHeap<T, Container>::Node::operator<=>(Node& obj) const {
    return key <=> obj.key;
}

template<std::three_way_comparable T, template<typename...> class Container>
std::weak_ordering GRon::FibonacciHeap<T, Container>::Node::operator<=>(T& obj) const {
    return key <=> obj;
}

/// Fibonacci Heap
template<std::three_way_comparable T, template<typename...> class Container>
size_t GRon::FibonacciHeap<T, Container>::size() const {
    return _size;
}

template<std::three_way_comparable T, template<typename...> class Container>
void GRon::FibonacciHeap<T, Container>::insert(const T& key) {
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

template<std::three_way_comparable T, template<typename...> class Container>
typename GRon::FibonacciHeap<T, Container>::Node* GRon::FibonacciHeap<T, Container>::get_minimum() {
    if (_clean) {


        std::optional<size_t> max_degree = std::nullopt;

        max_degree = std::log2f((double) size()) * 1.618;

        if (!max_degree.has_value()) return nullptr;

        Container<Node*> degree_list(max_degree.value(), nullptr);

        Node* current{nullptr};
        Node* node{nullptr};
        for (Node* root : root_list) {
            if (!root) continue;

            size_t degree = root->degree();
            current = *std::next(degree_list.begin(), degree);
            if (!current) {
                *std::next(degree_list.begin(), degree) = root;
                continue;
            }

            node = root;
            while (current) {
                if (node->key < current->key) {
                    current->parent = node;
                    node->children.push_back(current);
                } else {
                    node->parent = current;
                    current->children.push_back(node);
                    node = current;
                }

                *std::next(degree_list.begin(), degree) = nullptr;

                if (degree + 1 >= degree_list.size()) break;

                degree = node->degree();
                current = *std::next(degree_list.begin(), degree);
            }

            *std::next(degree_list.begin(), degree) = node;
        }

        root_list.swap(degree_list);
        for (auto& i : root_list) {
            if (i && (!_minimum || i->key <= _minimum->key)) {
                _minimum = i;
            }
        }

        _clean = false;
    }

    return _minimum;
}

template<std::three_way_comparable T, template<typename...> class Container>
std::optional<typename GRon::FibonacciHeap<T, Container>::Node> GRon::FibonacciHeap<T, Container>::pop_minimum() & {
    const Node* min = get_minimum();

    if (!min) return std::nullopt;

    for (Node* node : min->children) {
        node->parent = nullptr;
    }

    root_list.insert(root_list.end(), min->children.begin(), min->children.end());
    std::erase(root_list, min);

    _removed.push_back(&(*std::find(_nodes.begin(), _nodes.end(), *min)));

    _minimum = nullptr;
    _clean = true;
    _size--;

    return *min;
}

template<std::three_way_comparable T, template<typename...> class Container>
std::optional<typename GRon::FibonacciHeap<T, Container>::Node> GRon::FibonacciHeap<T, Container>::pop_minimum() && {
    const Node* min = get_minimum();

    if (!min) return std::nullopt;

    for (Node* node : min->children) {
        node->parent = nullptr;
    }

    root_list.insert(root_list.end(), min->children.begin(), min->children.end());
    std::erase(root_list, min);

    _removed.push_back(&(*std::find(_nodes.begin(), _nodes.end(), *min)));

    _minimum = nullptr;
    _clean = true;
    _size--;

    return std::move(*min);
}

template<std::three_way_comparable T, template<typename...> class Container>
void GRon::FibonacciHeap<T, Container>::cut_key(FibonacciHeap::Node* node, const T& key) {
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

template<std::three_way_comparable T, template<typename...> class Container>
void GRon::FibonacciHeap<T, Container>::alter_key(const T& key, const T& new_key) {
    auto old = std::find(_nodes.begin(), _nodes.end(), key);
    if (old == _nodes.end()) return;

    cut_key(&(*old), new_key);
}