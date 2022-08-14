#include "GRon/FibonacciHeap/BinomialHeap.hpp"

#include <algorithm>
#include <cmath>

// Node
template<std::three_way_comparable T>
size_t BinomialHeap<T>::Node::degree() const {
    return (size_t) std::max(log2((double) children.size()), 0.0);
}

template<std::three_way_comparable T>
size_t BinomialHeap<T>::Node::size() const {
    size_t ret = 1;

    for (auto i : children) {
        ret += i.size();
    }

    return ret;
}

template<std::three_way_comparable T>
std::ostream& BinomialHeap<T>::Node::streamInsertion(std::ostream &os) const {
    os << value << std::endl;
    for (auto i : children) {
        os << "|\t" << i << std::endl;
    }

    return os;
}

// Binomial Heap
template<std::three_way_comparable T>
size_t BinomialHeap<T>::size() const {
    size_t ret = 0;

    for (auto i : root_list){
        ret += i.size();
    }

    return ret;
}

template<std::three_way_comparable T>
void BinomialHeap<T>::insert(T value) {
    clean_flag = true;
    root_list.emplace_back(value);
}

template<std::three_way_comparable T>
std::optional<typename BinomialHeap<T>::Node> BinomialHeap<T>::get_minimum() {
    if (clean_flag) {
        std::optional<size_t> max_degree = std::nullopt;

        max_degree = std::log2(size());

        std::vector<std::optional<Node>> degree_list;
        unsigned long x = max_degree.value();
        if (max_degree.has_value()) {
            degree_list.assign(max_degree.value() + 1, std::nullopt);
        } else {
            return std::nullopt;
        }

        for (size_t i = 0; i < root_list.size(); i++) {
            size_t degree = root_list.at(i).degree();
            if (!degree_list.at(degree).has_value()) {
                degree_list.at(degree) = root_list.at(i);
                continue;
            }

            Node node = root_list.at(i);
            while (degree_list.at(degree).has_value()) {
                auto res = node.value <=> degree_list.at(degree).value().value;

                if (res < 0) {
                    node.children.push_back(degree_list.at(degree).value());
                } else {
                    degree_list.at(degree).value().children.push_back(node);
                    node = degree_list.at(degree).value();
                }

                degree_list.at(degree) = std::nullopt;

                if (degree + 1 >= degree_list.size()) break;

                degree++;
            }

            degree_list.at(degree) = node;
        }

        root_list.clear();
        for (auto i : degree_list) {
            if (i.has_value())
                root_list.push_back(i.value());
        }

        for (auto i : root_list) {
            if (!minimum.has_value() || i.value < minimum.value().value) {
                minimum = i;
                continue;
            }
        }

        clean_flag = false;
    }

    return minimum;
}


template<class Y>
std::ostream& operator<<(std::ostream& os, const BinomialHeap<Y>& obj) {
    for (auto i : obj.root_list){
        os << i << std::endl;
    }

    return os;
}