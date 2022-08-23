#include "GRon/FibonacciHeap/FibonacciHeap.hpp"
#include "benchmark/cppbenchmark.h"

#include <functional>
#include <queue>
#include <string>

#define run_inf CppBenchmark::Settings().Infinite().Attempts(50)
#define N 10000000
#define RATIO 65536

namespace GRon {
    template<typename T>
    class priority_queue_mfh : public FibonacciHeap<T> {
    public:

        priority_queue_mfh() = default;
        priority_queue_mfh(size_t n) : FibonacciHeap<T>(n) {}

        [[nodiscard]] typename FibonacciHeap<T>::Node& top() {
            return *this->get_minimum();
        }

        [[nodiscard]] bool empty() const {
            return this->location.empty();
        }

        void push(const T& value) {
            this->insert(value);
        }

        void pop() {
            this->pop_minimum();
        }
    };
}

template<typename T>
class HeapFixture : public virtual CppBenchmark::Fixture {
protected:
    T heap;

    void Initialize(CppBenchmark::Context& context) override { heap = T(); }
    void Cleanup(CppBenchmark::Context& context) override { heap = T(); }
};

template<typename T>
class HeapParamFixture : public virtual CppBenchmark::Fixture {
protected:
    T heap;

    void Initialize(CppBenchmark::Context& context) override { heap = T(static_cast<size_t>(context.x())); }
    void Cleanup(CppBenchmark::Context& context) override { heap = T(); }
};

template<class T>
void run(T& heap, size_t n, int ratio, bool invert = false) {
    for (int i = 0; i < n; ++i) {
        if (!(i % ratio) ^ invert) {
            heap.top();
            continue;
        }

        heap.push(std::to_string(i));
    }
}

/**
 * GRon::priority_queue_mfh
 */

BENCHMARK_FIXTURE(HeapParamFixture<GRon::priority_queue_mfh<std::string>>, "pqmfh", run_inf.Param(N)) {
    run(heap, N, RATIO);
    context.Cancel();
}

/**
 * std::priority_queue
 */

BENCHMARK_FIXTURE(HeapFixture<std::priority_queue<std::string>>, "std::pq", run_inf) {
    run(heap, N, RATIO);
    context.Cancel();
}

BENCHMARK_MAIN()