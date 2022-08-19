#include "GRon/FibonacciHeap/FibonacciHeap.hpp"

#include <algorithm>
#include <cmath>

// Node
template<std::three_way_comparable T>
size_t FibonacciHeap<T>::Node::degree() const {
    return children.size();
}

template<std::three_way_comparable T>
size_t FibonacciHeap<T>::Node::size() const {
    size_t ret = 1;

    for (auto& i : children) {
        ret += i->size();
    }

    return ret;
}

template<std::three_way_comparable T>
bool FibonacciHeap<T>::Node::operator==(const FibonacciHeap::Node& obj) const {
    return key == obj.key;
}

template<std::three_way_comparable T>
std::weak_ordering FibonacciHeap<T>::Node::operator<=>(Node& obj) const {
    return key <=> obj.key;
}

template<std::three_way_comparable T>
std::ostream& FibonacciHeap<T>::Node::streamInsertion(std::ostream &os) const {
    os << key << '[';
    for (auto& i : children) {
        os << *i;
    }

    os << ']';

    return os;
}

// Binomial Heap
template<std::three_way_comparable T>
size_t FibonacciHeap<T>::size() const {
    return location.size();
}

template<std::three_way_comparable T>
void FibonacciHeap<T>::insert(const T& key) {
    clean_flag = true;
    location.emplace(key, key);
    root_list.push_back(&location.at(key));
}

template<std::three_way_comparable T>
typename FibonacciHeap<T>::Node* FibonacciHeap<T>::get_minimum() {
    if (clean_flag) {
        std::optional<size_t> max_degree = std::nullopt;

        max_degree = ceil(std::log2f((double) size()) * 1.618);

        std::vector<Node*> degree_list;
        if (max_degree.has_value()) {
            degree_list.assign(max_degree.value() + 1, nullptr);
        } else {
            return nullptr;
        }

        for (size_t i = 0; i < root_list.size(); i++) {
            size_t degree = root_list.at(i)->degree();
            if (degree_list.at(degree) == nullptr) {
                degree_list.at(degree) = root_list.at(i);
                continue;
            }

            Node* node = root_list.at(i);
            while (degree_list.at(degree) != nullptr) {
                if (node->key < degree_list.at(degree)->key) {
                    degree_list.at(degree)->parent = node;
                    node->children.push_back(degree_list.at(degree));
                } else {
                    node->parent = degree_list.at(degree);
                    degree_list.at(degree)->children.push_back(node);
                    node = degree_list.at(degree);
                }

                degree_list.at(degree) = nullptr;

                if (degree + 1 >= degree_list.size()) break;

                degree = node->degree();
            }

            degree_list.at(degree) = node;
        }

        root_list.clear();
        for (auto i : degree_list) {
            if (i != nullptr) {
                root_list.push_back(i);
            }
        }

        for (auto& i : root_list) {
            if (minimum == nullptr || i->key <= minimum->key) {
                minimum = i;
                continue;
            }
        }

        clean_flag = false;
    }

    return minimum;
}

template<std::three_way_comparable T>
std::optional<typename FibonacciHeap<T>::Node> FibonacciHeap<T>::pop_minimum() {
    const Node* pop_min = get_minimum();

    if (pop_min == nullptr) return std::nullopt;

    Node ret{*pop_min};

    root_list.insert(root_list.end(), pop_min->children.begin(), pop_min->children.end());
    root_list.erase(std::remove(root_list.begin(), root_list.end(), pop_min), root_list.end());
    location.erase(pop_min->key);

    minimum = nullptr;
    clean_flag = true;

    return ret;
}

template<std::three_way_comparable T>
void FibonacciHeap<T>::cut_key(FibonacciHeap::Node& node, const T& key) {
    if (!location.contains(key)) return;

    clean_flag = true;

    node.key = key;
    node.marked = false;
    Node* old_parent = node.parent;
    node.parent = nullptr;

    root_list.push_back(&node);

    if (old_parent != nullptr) {
        old_parent->children.erase(std::remove(old_parent->children.begin(), old_parent->children.end(), &node), old_parent->children.end());

        if (!old_parent->marked) {
            old_parent->marked = true;
        } else {
            cut_key(*old_parent, old_parent->key);
        }
    }
}

template<std::three_way_comparable T>
void FibonacciHeap<T>::alter_key(const T& key, const T& new_key) {
    if (!location.contains(key) && location.contains(new_key)) return;

    auto old = location.extract(key);
    old.key() = new_key;
    location.insert(std::move(old));

    cut_key(location.at(new_key), new_key);
}

template<class Y>
std::ostream& operator<<(std::ostream& os, const FibonacciHeap<Y>& obj) {
    for (auto& i : obj.root_list){
        os << *i << std::endl;
    }

    return os;
}