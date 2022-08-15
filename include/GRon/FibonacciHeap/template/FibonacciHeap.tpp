#include "GRon/FibonacciHeap/FibonacciHeap.hpp"

#include <algorithm>
#include <cmath>

// Node
template<std::three_way_comparable T>
size_t FibonacciHeap<T>::Node::degree() const {
    return (size_t) std::max(log2((double) children.size()), 0.0);
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
    os << key << '(' << this->address() << ')' << std::endl;
    for (auto& i : children) {
        os << i;
    }

    return os;
}

// Binomial Heap
template<std::three_way_comparable T>
size_t FibonacciHeap<T>::size() const {
    size_t ret = 0;

    for (auto& i : root_list){
        ret += i->size();
    }

    return ret;
}

template<std::three_way_comparable T>
void FibonacciHeap<T>::insert(const T& key) {
    clean_flag = true;
    location.template emplace(key, key);
    root_list.push_back(&location.at(key));
}

template<std::three_way_comparable T>
typename FibonacciHeap<T>::Node* FibonacciHeap<T>::get_minimum() {
    if (clean_flag) {
        std::optional<size_t> max_degree = std::nullopt;

        max_degree = std::log2(size());

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
                auto res = node->key <=> degree_list.at(degree)->key;

                if (res < 0) {
                    degree_list.at(degree)->parent.reset(node);
                    node->children.push_back(degree_list.at(degree));
                } else {
                    node->parent.reset(degree_list.at(degree));
                    degree_list.at(degree)->children.push_back(node);
                    node = degree_list.at(degree);
                }

                degree_list.at(degree) = nullptr;

                if (degree + 1 >= degree_list.size()) break;

                degree++;
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
            if (minimum == nullptr || i->key < minimum->key) {
                minimum = i;
                continue;
            }
        }

        clean_flag = false;
    }

    return minimum;
}

template<std::three_way_comparable T>
typename FibonacciHeap<T>::Node* FibonacciHeap<T>::pop_minimum() {
    const std::shared_ptr<Node> ret = get_minimum();

    if (ret != nullptr) {
        root_list.insert(root_list.end(), ret->children.begin(), ret->children.end());
        root_list.erase(std::remove(root_list.begin(), root_list.end(), ret), root_list.end());
    }

    clean_flag = true;

    return ret;
}

template<std::three_way_comparable T>
void FibonacciHeap<T>::cut_key(FibonacciHeap::Node& node, const T& key) {
    if (!location.contains(key)) return;

    clean_flag = true;

    node.key = key;
    node.marked = false;
    std::shared_ptr<Node> old_parent = node.parent;
    node.parent = nullptr;

    root_list.push_back(&node);

    if (old_parent != nullptr) {
        node.parent->children.erase(
                std::remove(node.parent->children.begin(), node.parent->children.end(), &node),
                node.parent->children.end());

        if (!node.parent->marked) {
            node.parent->marked = true;
        } else {
            cut_key(*node.parent, node.parent->key);
        }
    }
}

template<std::three_way_comparable T>
void FibonacciHeap<T>::alter_key(const T& key, const T& new_key) {
    if (!location.contains(key) && location.contains(new_key)) return;

    auto old = location.extract(key);
    location.insert(std::move(old));
    location.erase(key);

    cut_key(location.at(new_key), new_key);
}

template<class Y>
std::ostream& operator<<(std::ostream& os, const FibonacciHeap<Y>& obj) {
    for (auto& i : obj.root_list){
        os << i;
    }

    return os;
}