#include "GRon/FibonacciHeap/FibonacciHeap.hpp"
#include "benchmark/cppbenchmark.h"

#include <functional>
#include <queue>

namespace GRon {
    template<typename T>
    class priority_queue_mfh : public FibonacciHeap<T> {
    public:
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
    void Cleanup(CppBenchmark::Context& context) override {}
};

template<class T>
void run(T& heap, size_t n, int ratio) {
    for (int i = 0; i < n; ++i) {
        if (!rand() % ratio) {
            heap.top();
            continue;
        }

        heap.push((rand() % 1000) + i);
    }
}

/**
 * GRon::priority_queue_mfh, n=100
 */
BENCHMARK_FIXTURE(HeapFixture<GRon::priority_queue_mfh<int>>, "run(GRon::priority_queue_mfh, n=100, ratio=4)") {
    run(heap, 100, 4);
}

BENCHMARK_FIXTURE(HeapFixture<GRon::priority_queue_mfh<int>>, "run(GRon::priority_queue_mfh, n=100, ratio=8)") {
    run(heap, 100, 8);
}

BENCHMARK_FIXTURE(HeapFixture<GRon::priority_queue_mfh<int>>, "run(GRon::priority_queue_mfh, n=100, ratio=16)") {
    run(heap, 100, 16);
}

BENCHMARK_FIXTURE(HeapFixture<GRon::priority_queue_mfh<int>>, "run(GRon::priority_queue_mfh, n=100, ratio=32)") {
    run(heap, 100, 32);
}

/**
 * std::priority_queue, n=100
 */
BENCHMARK_FIXTURE(HeapFixture<std::priority_queue<int>>, "run(std::priority_queue, n=100, ratio=4)") {
    run(heap, 100, 4);
}

BENCHMARK_FIXTURE(HeapFixture<std::priority_queue<int>>, "run(std::priority_queue, n=100, ratio=8)") {
    run(heap, 100, 8);
}

BENCHMARK_FIXTURE(HeapFixture<std::priority_queue<int>>, "run(std::priority_queue, n=100, ratio=16)") {
    run(heap, 100, 16);
}

BENCHMARK_FIXTURE(HeapFixture<std::priority_queue<int>>, "run(std::priority_queue, n=100, ratio=32)") {
    run(heap, 100, 32);
}

/**
 * GRon::priority_queue_mfh, n=1000
 */
BENCHMARK_FIXTURE(HeapFixture<GRon::priority_queue_mfh<int>>, "run(GRon::priority_queue_mfh, n=1000, ratio=4)") {
    run(heap, 1000, 4);
}

BENCHMARK_FIXTURE(HeapFixture<GRon::priority_queue_mfh<int>>, "run(GRon::priority_queue_mfh, n=1000, ratio=8)") {
    run(heap, 1000, 8);
}

BENCHMARK_FIXTURE(HeapFixture<GRon::priority_queue_mfh<int>>, "run(GRon::priority_queue_mfh, n=1000, ratio=16)") {
    run(heap, 1000, 16);
}

BENCHMARK_FIXTURE(HeapFixture<GRon::priority_queue_mfh<int>>, "run(GRon::priority_queue_mfh, n=1000, ratio=32)") {
    run(heap, 1000, 32);
}

BENCHMARK_FIXTURE(HeapFixture<GRon::priority_queue_mfh<int>>, "run(GRon::priority_queue_mfh, n=1000, ratio=64)") {
    run(heap, 1000, 64);
}

BENCHMARK_FIXTURE(HeapFixture<GRon::priority_queue_mfh<int>>, "run(GRon::priority_queue_mfh, n=1000, ratio=128)") {
    run(heap, 1000, 128);
}

/**
 * std::priority_queue, n=1000
 */
BENCHMARK_FIXTURE(HeapFixture<std::priority_queue<int>>, "run(std::priority_queue, n=1000, ratio=4)") {
    run(heap, 1000, 4);
}

BENCHMARK_FIXTURE(HeapFixture<std::priority_queue<int>>, "run(std::priority_queue, n=1000, ratio=8)") {
    run(heap, 1000, 8);
}

BENCHMARK_FIXTURE(HeapFixture<std::priority_queue<int>>, "run(std::priority_queue, n=1000, ratio=16)") {
    run(heap, 1000, 16);
}

BENCHMARK_FIXTURE(HeapFixture<std::priority_queue<int>>, "run(std::priority_queue, n=1000, ratio=32)") {
    run(heap, 1000, 32);
}

BENCHMARK_FIXTURE(HeapFixture<std::priority_queue<int>>, "run(std::priority_queue, n=1000, ratio=64)") {
    run(heap, 1000, 64);
}

BENCHMARK_FIXTURE(HeapFixture<std::priority_queue<int>>, "run(std::priority_queue, n=1000, ratio=128)") {
    run(heap, 1000, 128);
}

/**
 * GRon::priority_queue_mfh, n=10000
 */
BENCHMARK_FIXTURE(HeapFixture<GRon::priority_queue_mfh<int>>, "run(GRon::priority_queue_mfh, n=10000, ratio=4)") {
    run(heap, 10000, 4);
}

BENCHMARK_FIXTURE(HeapFixture<GRon::priority_queue_mfh<int>>, "run(GRon::priority_queue_mfh, n=10000, ratio=8)") {
    run(heap, 10000, 8);
}

BENCHMARK_FIXTURE(HeapFixture<GRon::priority_queue_mfh<int>>, "run(GRon::priority_queue_mfh, n=10000, ratio=16)") {
    run(heap, 10000, 16);
}

BENCHMARK_FIXTURE(HeapFixture<GRon::priority_queue_mfh<int>>, "run(GRon::priority_queue_mfh, n=10000, ratio=32)") {
    run(heap, 10000, 32);
}

BENCHMARK_FIXTURE(HeapFixture<GRon::priority_queue_mfh<int>>, "run(GRon::priority_queue_mfh, n=10000, ratio=64)") {
    run(heap, 10000, 64);
}

BENCHMARK_FIXTURE(HeapFixture<GRon::priority_queue_mfh<int>>, "run(GRon::priority_queue_mfh, n=10000, ratio=128)") {
    run(heap, 10000, 128);
}

BENCHMARK_FIXTURE(HeapFixture<GRon::priority_queue_mfh<int>>, "run(GRon::priority_queue_mfh, n=10000, ratio=256)") {
    run(heap, 10000, 256);
}

BENCHMARK_FIXTURE(HeapFixture<GRon::priority_queue_mfh<int>>, "run(GRon::priority_queue_mfh, n=10000, ratio=512)") {
    run(heap, 10000, 512);
}

/**
 * std::priority_queue, n=10000
 */
BENCHMARK_FIXTURE(HeapFixture<std::priority_queue<int>>, "run(std::priority_queue, n=10000, ratio=4)") {
    run(heap, 10000, 4);
}

BENCHMARK_FIXTURE(HeapFixture<std::priority_queue<int>>, "run(std::priority_queue, n=10000, ratio=8)") {
    run(heap, 10000, 8);
}

BENCHMARK_FIXTURE(HeapFixture<std::priority_queue<int>>, "run(std::priority_queue, n=10000, ratio=16)") {
    run(heap, 10000, 16);
}

BENCHMARK_FIXTURE(HeapFixture<std::priority_queue<int>>, "run(std::priority_queue, n=10000, ratio=32)") {
    run(heap, 10000, 32);
}

BENCHMARK_FIXTURE(HeapFixture<std::priority_queue<int>>, "run(std::priority_queue, n=10000, ratio=64)") {
    run(heap, 10000, 64);
}

BENCHMARK_FIXTURE(HeapFixture<std::priority_queue<int>>, "run(std::priority_queue, n=10000, ratio=128)") {
    run(heap, 10000, 128);
}

BENCHMARK_FIXTURE(HeapFixture<std::priority_queue<int>>, "run(std::priority_queue, n=10000, ratio=256)") {
    run(heap, 10000, 256);
}

BENCHMARK_FIXTURE(HeapFixture<std::priority_queue<int>>, "run(std::priority_queue, n=10000, ratio=512)") {
    run(heap, 10000, 512);
}

/**
 * GRon::priority_queue_mfh, n=100000
 */
BENCHMARK_FIXTURE(HeapFixture<GRon::priority_queue_mfh<int>>, "run(GRon::priority_queue_mfh, n=100000, ratio=4)") {
    run(heap, 100000, 4);
}

BENCHMARK_FIXTURE(HeapFixture<GRon::priority_queue_mfh<int>>, "run(GRon::priority_queue_mfh, n=100000, ratio=8)") {
    run(heap, 100000, 8);
}

BENCHMARK_FIXTURE(HeapFixture<GRon::priority_queue_mfh<int>>, "run(GRon::priority_queue_mfh, n=100000, ratio=16)") {
    run(heap, 100000, 16);
}

BENCHMARK_FIXTURE(HeapFixture<GRon::priority_queue_mfh<int>>, "run(GRon::priority_queue_mfh, n=100000, ratio=32)") {
    run(heap, 100000, 32);
}

BENCHMARK_FIXTURE(HeapFixture<GRon::priority_queue_mfh<int>>, "run(GRon::priority_queue_mfh, n=100000, ratio=64)") {
    run(heap, 100000, 64);
}

BENCHMARK_FIXTURE(HeapFixture<GRon::priority_queue_mfh<int>>, "run(GRon::priority_queue_mfh, n=100000, ratio=128)") {
    run(heap, 100000, 128);
}

BENCHMARK_FIXTURE(HeapFixture<GRon::priority_queue_mfh<int>>, "run(GRon::priority_queue_mfh, n=100000, ratio=256)") {
    run(heap, 100000, 256);
}

BENCHMARK_FIXTURE(HeapFixture<GRon::priority_queue_mfh<int>>, "run(GRon::priority_queue_mfh, n=100000, ratio=512)") {
    run(heap, 100000, 512);
}

BENCHMARK_FIXTURE(HeapFixture<GRon::priority_queue_mfh<int>>, "run(GRon::priority_queue_mfh, n=100000, ratio=1024)") {
    run(heap, 100000, 1024);
}

BENCHMARK_FIXTURE(HeapFixture<GRon::priority_queue_mfh<int>>, "run(GRon::priority_queue_mfh, n=100000, ratio=2048)") {
    run(heap, 100000, 2048);
}

/**
 * std::priority_queue, n=100000
 */
BENCHMARK_FIXTURE(HeapFixture<std::priority_queue<int>>, "run(std::priority_queue, n=100000, ratio=4)") {
    run(heap, 100000, 4);
}

BENCHMARK_FIXTURE(HeapFixture<std::priority_queue<int>>, "run(std::priority_queue, n=100000, ratio=8)") {
    run(heap, 100000, 8);
}

BENCHMARK_FIXTURE(HeapFixture<std::priority_queue<int>>, "run(std::priority_queue, n=100000, ratio=16)") {
    run(heap, 100000, 16);
}

BENCHMARK_FIXTURE(HeapFixture<std::priority_queue<int>>, "run(std::priority_queue, n=100000, ratio=32)") {
    run(heap, 100000, 32);
}

BENCHMARK_FIXTURE(HeapFixture<std::priority_queue<int>>, "run(std::priority_queue, n=100000, ratio=64)") {
    run(heap, 100000, 64);
}

BENCHMARK_FIXTURE(HeapFixture<std::priority_queue<int>>, "run(std::priority_queue, n=100000, ratio=128)") {
    run(heap, 100000, 128);
}

BENCHMARK_FIXTURE(HeapFixture<std::priority_queue<int>>, "run(std::priority_queue, n=100000, ratio=256)") {
    run(heap, 100000, 256);
}

BENCHMARK_FIXTURE(HeapFixture<std::priority_queue<int>>, "run(std::priority_queue, n=100000, ratio=512)") {
    run(heap, 100000, 512);
}

BENCHMARK_FIXTURE(HeapFixture<std::priority_queue<int>>, "run(std::priority_queue, n=100000, ratio=1024)") {
    run(heap, 100000, 1024);
}

BENCHMARK_FIXTURE(HeapFixture<std::priority_queue<int>>, "run(std::priority_queue, n=100000, ratio=2048)") {
    run(heap, 100000, 2048);
}

BENCHMARK_MAIN()