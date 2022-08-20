#include "GRon/FibonacciHeap/FibonacciHeap.hpp"

#include <algorithm>
#include <cmath>

// Node
template<std::three_way_comparable T, template<typename, typename> typename Container>
size_t FibonacciHeap<T, Container>::Node::degree() const {
    return children.size();
}

template<std::three_way_comparable T, template<typename, typename> typename Container>
size_t FibonacciHeap<T, Container>::Node::size() const {
    size_t ret = 1;

    for (auto& i : children) {
        ret += i->size();
    }

    return ret;
}

template<std::three_way_comparable T, template<typename, typename> typename Container>
bool FibonacciHeap<T, Container>::Node::operator==(const FibonacciHeap::Node& obj) const {
    return key == obj.key;
}

template<std::three_way_comparable T, template<typename, typename> typename Container>
bool FibonacciHeap<T, Container>::Node::operator==(const T& obj) const {
    return key == obj;
}

template<std::three_way_comparable T, template<typename, typename> typename Container>
std::weak_ordering FibonacciHeap<T, Container>::Node::operator<=>(Node& obj) const {
    return key <=> obj.key;
}

template<std::three_way_comparable T, template<typename, typename> typename Container>
std::weak_ordering FibonacciHeap<T, Container>::Node::operator<=>(T& obj) const {
    return key <=> obj;
}

// Binomial Heap
template<std::three_way_comparable T, template<typename, typename> typename Container>
size_t FibonacciHeap<T, Container>::size() const {
    return _size;
}

template<std::three_way_comparable T, template<typename, typename> typename Container>
void FibonacciHeap<T, Container>::insert(const T& key) {
    _clean = true;
    _size++;

    if (_removed.empty()) {
        root_list.push_back(&_nodes.emplace_back(key));
        return;
    }

    auto it = _removed.back();
    *it = Node(key);
    root_list.push_back(&(*it));
    _removed.pop_back();
}

template<std::three_way_comparable T, template<typename, typename> typename Container>
typename FibonacciHeap<T, Container>::Node* FibonacciHeap<T, Container>::get_minimum() {
    if (_clean) {
        std::optional<size_t> max_degree = std::nullopt;

        max_degree = ceil(std::log2f((double) size()) * 1.618);

        std::vector<Node*> degree_list;
        if (max_degree.has_value()) {
            degree_list.assign(max_degree.value() + 1, nullptr);
        } else {
            return nullptr;
        }

        Node* current{nullptr};
        Node* node{nullptr};
        for (size_t i = 0; i < root_list.size(); i++) {
            size_t degree = root_list[i]->degree();
            current = degree_list[degree];
            if (current == nullptr) {
                degree_list[degree] = root_list[i];
                continue;
            }

            node = root_list[i];
            while (current) {
                if (node->key < current->key) {
                    current->parent = node;
                    node->children.push_back(current);
                } else {
                    node->parent = current;
                    current->children.push_back(node);
                    node = current;
                }

                degree_list[degree] = nullptr;

                if (degree + 1 >= degree_list.size()) break;

                degree = node->degree();
                current = degree_list[degree];
            }

            degree_list[degree] = node;
        }

        root_list.clear();
        for (auto i : degree_list) {
            if (i != nullptr) {
                root_list.push_back(i);
            }
        }

        for (auto& i : root_list) {
            if (!_minimum || i->key <= _minimum->key) {
                _minimum = i;
                continue;
            }
        }

        _clean = false;
    }

    return _minimum;
}

template<std::three_way_comparable T, template<typename, typename> typename Container>
std::optional<typename FibonacciHeap<T, Container>::Node> FibonacciHeap<T, Container>::pop_minimum() {
    const Node* min = get_minimum();

    if (min == nullptr) return std::nullopt;

    for (Node* node : min->children) {
        node->parent = nullptr;
    }

    root_list.insert(root_list.end(), min->children.begin(), min->children.end());
    root_list.erase(std::remove(root_list.begin(), root_list.end(), min), root_list.end());

    // ToDo: Optimize return
    _removed.push_back(std::find(_nodes.begin(), _nodes.end(), *min));
    Node ret{std::move(*min)};

    _minimum = nullptr;
    _clean = true;
    _size--;

    return ret;
}

template<std::three_way_comparable T, template<typename, typename> typename Container>
void FibonacciHeap<T, Container>::cut_key(FibonacciHeap::Node* node, const T& key) {
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

template<std::three_way_comparable T, template<typename, typename> typename Container>
void FibonacciHeap<T, Container>::alter_key(const T& key, const T& new_key) {
    auto old = std::find(_nodes.begin(), _nodes.end(), key);
    if (old == _nodes.end()) return;

    cut_key(&(*old), new_key);
}