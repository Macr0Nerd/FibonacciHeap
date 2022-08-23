#include "GRon/FibonacciHeap/FibonacciHeap.hpp"
#include "benchmark/cppbenchmark.h"

#include <functional>
#include <queue>

#define run_inf CppBenchmark::Settings().Infinite().Attempts(50)

namespace GRon {
    template<typename T>
class priority_queue_mfh : public FibonacciHeap<T> {
    public:

        priority_queue_mfh() = default;
        explicit priority_queue_mfh(size_t n) : FibonacciHeap<T>(n) {}

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

        heap.push(rand() % n);
    }
}


/**
 * GRon::priority_queue_mfh, n=100
 */
BENCHMARK_FIXTURE(HeapParamFixture<GRon::priority_queue_mfh<int>>, "run(GRon::priority_queue_mfh, n=100, ratio=4)", run_inf.Param(100)) {
    run(heap, 100, 4);
    context.Cancel();
}

BENCHMARK_FIXTURE(HeapParamFixture<GRon::priority_queue_mfh<int>>, "run(GRon::priority_queue_mfh, n=100, ratio=8)", run_inf.Param(100)) {
    run(heap, 100, 8);
    context.Cancel();
}

BENCHMARK_FIXTURE(HeapParamFixture<GRon::priority_queue_mfh<int>>, "run(GRon::priority_queue_mfh, n=100, ratio=16)", run_inf.Param(100)) {
    run(heap, 100, 16);
    context.Cancel();
}

BENCHMARK_FIXTURE(HeapParamFixture<GRon::priority_queue_mfh<int>>, "run(GRon::priority_queue_mfh, n=100, ratio=32)", run_inf.Param(100)) {
    run(heap, 100, 32);
    context.Cancel();
}

/**
 * std::priority_queue, n=100
 */
BENCHMARK_FIXTURE(HeapFixture<std::priority_queue<int>>, "run(std::priority_queue, n=100, ratio=4)", run_inf) {
   run(heap, 100, 4);
   context.Cancel();
}

BENCHMARK_FIXTURE(HeapFixture<std::priority_queue<int>>, "run(std::priority_queue, n=100, ratio=8)", run_inf) {
   run(heap, 100, 8);
   context.Cancel();
}

BENCHMARK_FIXTURE(HeapFixture<std::priority_queue<int>>, "run(std::priority_queue, n=100, ratio=16)", run_inf) {
   run(heap, 100, 16);
   context.Cancel();
}

BENCHMARK_FIXTURE(HeapFixture<std::priority_queue<int>>, "run(std::priority_queue, n=100, ratio=32)", run_inf) {
   run(heap, 100, 32);
   context.Cancel();
}

/**
 * GRon::priority_queue_mfh, n=1000
 */

BENCHMARK_FIXTURE(HeapParamFixture<GRon::priority_queue_mfh<int>>, "run(GRon::priority_queue_mfh, n=1000, ratio=8)", run_inf.Param(1000)) {
    run(heap, 1000, 8);
    context.Cancel();
}

BENCHMARK_FIXTURE(HeapParamFixture<GRon::priority_queue_mfh<int>>, "run(GRon::priority_queue_mfh, n=1000, ratio=16)", run_inf.Param(1000)) {
    run(heap, 1000, 16);
    context.Cancel();
}

BENCHMARK_FIXTURE(HeapParamFixture<GRon::priority_queue_mfh<int>>, "run(GRon::priority_queue_mfh, n=1000, ratio=32)", run_inf.Param(1000)) {
    run(heap, 1000, 32);
    context.Cancel();
}

BENCHMARK_FIXTURE(HeapParamFixture<GRon::priority_queue_mfh<int>>, "run(GRon::priority_queue_mfh, n=1000, ratio=64)", run_inf.Param(1000)) {
    run(heap, 1000, 64);
    context.Cancel();
}

BENCHMARK_FIXTURE(HeapParamFixture<GRon::priority_queue_mfh<int>>, "run(GRon::priority_queue_mfh, n=1000, ratio=128)", run_inf.Param(1000)) {
    run(heap, 1000, 128);
    context.Cancel();
}

BENCHMARK_FIXTURE(HeapParamFixture<GRon::priority_queue_mfh<int>>, "run(GRon::priority_queue_mfh, n=1000, ratio=256)", run_inf.Param(1000)) {
    run(heap, 1000, 256);
    context.Cancel();
}

/**
 * std::priority_queue, n=1000
 */

BENCHMARK_FIXTURE(HeapFixture<std::priority_queue<int>>, "run(std::priority_queue, n=1000, ratio=8)", run_inf) {
   run(heap, 1000, 8);
   context.Cancel();
}

BENCHMARK_FIXTURE(HeapFixture<std::priority_queue<int>>, "run(std::priority_queue, n=1000, ratio=16)", run_inf) {
   run(heap, 1000, 16);
   context.Cancel();
}

BENCHMARK_FIXTURE(HeapFixture<std::priority_queue<int>>, "run(std::priority_queue, n=1000, ratio=32)", run_inf) {
   run(heap, 1000, 32);
   context.Cancel();
}

BENCHMARK_FIXTURE(HeapFixture<std::priority_queue<int>>, "run(std::priority_queue, n=1000, ratio=64)", run_inf) {
   run(heap, 1000, 64);
   context.Cancel();
}

BENCHMARK_FIXTURE(HeapFixture<std::priority_queue<int>>, "run(std::priority_queue, n=1000, ratio=128)", run_inf) {
   run(heap, 1000, 128);
   context.Cancel();
}

BENCHMARK_FIXTURE(HeapFixture<std::priority_queue<int>>, "run(std::priority_queue, n=1000, ratio=256)", run_inf) {
    run(heap, 1000, 256);
    context.Cancel();
}

/**
 * GRon::priority_queue_mfh, n=10000
 */

BENCHMARK_FIXTURE(HeapParamFixture<GRon::priority_queue_mfh<int>>, "run(GRon::priority_queue_mfh, n=10000, ratio=32)", run_inf.Param(10000)) {
    run(heap, 10000, 32);
    context.Cancel();
}

BENCHMARK_FIXTURE(HeapParamFixture<GRon::priority_queue_mfh<int>>, "run(GRon::priority_queue_mfh, n=10000, ratio=64)", run_inf.Param(10000)) {
    run(heap, 10000, 64);
    context.Cancel();
}

BENCHMARK_FIXTURE(HeapParamFixture<GRon::priority_queue_mfh<int>>, "run(GRon::priority_queue_mfh, n=10000, ratio=128)", run_inf.Param(10000)) {
    run(heap, 10000, 128);
    context.Cancel();
}

BENCHMARK_FIXTURE(HeapParamFixture<GRon::priority_queue_mfh<int>>, "run(GRon::priority_queue_mfh, n=10000, ratio=256)", run_inf.Param(10000)) {
    run(heap, 10000, 256);
    context.Cancel();
}

BENCHMARK_FIXTURE(HeapParamFixture<GRon::priority_queue_mfh<int>>, "run(GRon::priority_queue_mfh, n=10000, ratio=512)", run_inf.Param(10000)) {
    run(heap, 10000, 512);
    context.Cancel();
}

BENCHMARK_FIXTURE(HeapParamFixture<GRon::priority_queue_mfh<int>>, "run(GRon::priority_queue_mfh, n=10000, ratio=1024)", run_inf.Param(10000)) {
    run(heap, 10000, 1024);
    context.Cancel();
}

/**
 * std::priority_queue, n=10000
 */

BENCHMARK_FIXTURE(HeapFixture<std::priority_queue<int>>, "run(std::priority_queue, n=10000, ratio=32)", run_inf) {
   run(heap, 10000, 32);
   context.Cancel();
}

BENCHMARK_FIXTURE(HeapFixture<std::priority_queue<int>>, "run(std::priority_queue, n=10000, ratio=64)", run_inf) {
   run(heap, 10000, 64);
   context.Cancel();
}

BENCHMARK_FIXTURE(HeapFixture<std::priority_queue<int>>, "run(std::priority_queue, n=10000, ratio=128)", run_inf) {
   run(heap, 10000, 128);
   context.Cancel();
}

BENCHMARK_FIXTURE(HeapFixture<std::priority_queue<int>>, "run(std::priority_queue, n=10000, ratio=256)", run_inf) {
   run(heap, 10000, 256);
   context.Cancel();
}

BENCHMARK_FIXTURE(HeapFixture<std::priority_queue<int>>, "run(std::priority_queue, n=10000, ratio=512)", run_inf) {
   run(heap, 10000, 512);
   context.Cancel();
}

BENCHMARK_FIXTURE(HeapFixture<std::priority_queue<int>>, "run(std::priority_queue, n=10000, ratio=1024)", run_inf) {
    run(heap, 10000, 1024);
    context.Cancel();
}


/**
* GRon::priority_queue_mfh, n=100000
*/

BENCHMARK_FIXTURE(HeapParamFixture<GRon::priority_queue_mfh<int>>, "run(GRon::priority_queue_mfh, n=100000, ratio=128)", run_inf.Param(100000)) {
    run(heap, 100000, 128);
    context.Cancel();
}

BENCHMARK_FIXTURE(HeapParamFixture<GRon::priority_queue_mfh<int>>, "run(GRon::priority_queue_mfh, n=100000, ratio=256)", run_inf.Param(100000)) {
    run(heap, 100000, 256);
    context.Cancel();
}

BENCHMARK_FIXTURE(HeapParamFixture<GRon::priority_queue_mfh<int>>, "run(GRon::priority_queue_mfh, n=100000, ratio=512)", run_inf.Param(100000)) {
    run(heap, 100000, 512);
    context.Cancel();
}

BENCHMARK_FIXTURE(HeapParamFixture<GRon::priority_queue_mfh<int>>, "run(GRon::priority_queue_mfh, n=100000, ratio=1024)", run_inf.Param(100000)) {
    run(heap, 100000, 1024);
    context.Cancel();
}

BENCHMARK_FIXTURE(HeapParamFixture<GRon::priority_queue_mfh<int>>, "run(GRon::priority_queue_mfh, n=100000, ratio=2048)", run_inf.Param(100000)) {
    run(heap, 100000, 2048);
    context.Cancel();
}
BENCHMARK_FIXTURE(HeapParamFixture<GRon::priority_queue_mfh<int>>, "run(GRon::priority_queue_mfh, n=100000, ratio=4096)", run_inf.Param(100000)) {
    run(heap, 100000, 4096);
    context.Cancel();
}


/**
 * std::priority_queue, n=100000
 */

BENCHMARK_FIXTURE(HeapFixture<std::priority_queue<int>>, "run(std::priority_queue, n=100000, ratio=128)", run_inf) {
    run(heap, 100000, 128);
    context.Cancel();
}

BENCHMARK_FIXTURE(HeapFixture<std::priority_queue<int>>, "run(std::priority_queue, n=100000, ratio=256)", run_inf) {
    run(heap, 100000, 256);
    context.Cancel();
}

BENCHMARK_FIXTURE(HeapFixture<std::priority_queue<int>>, "run(std::priority_queue, n=100000, ratio=512)", run_inf) {
    run(heap, 100000, 512);
    context.Cancel();
}

BENCHMARK_FIXTURE(HeapFixture<std::priority_queue<int>>, "run(std::priority_queue, n=100000, ratio=1024)", run_inf) {
    run(heap, 100000, 1024);
    context.Cancel();
}

BENCHMARK_FIXTURE(HeapFixture<std::priority_queue<int>>, "run(std::priority_queue, n=100000, ratio=2048)", run_inf) {
    run(heap, 100000, 2048);
    context.Cancel();
}

BENCHMARK_FIXTURE(HeapFixture<std::priority_queue<int>>, "run(std::priority_queue, n=100000, ratio=4096)", run_inf) {
    run(heap, 100000, 4096);
    context.Cancel();
}

/**
* GRon::priority_queue_mfh, n=1000000
*/

BENCHMARK_FIXTURE(HeapParamFixture<GRon::priority_queue_mfh<int>>, "run(GRon::priority_queue_mfh, n=1000000, ratio=512)", run_inf.Param(1000000)) {
    run(heap, 1000000, 512);
    context.Cancel();
}

BENCHMARK_FIXTURE(HeapParamFixture<GRon::priority_queue_mfh<int>>, "run(GRon::priority_queue_mfh, n=1000000, ratio=1024)", run_inf.Param(1000000)) {
    run(heap, 1000000, 1024);
    context.Cancel();
}

BENCHMARK_FIXTURE(HeapParamFixture<GRon::priority_queue_mfh<int>>, "run(GRon::priority_queue_mfh, n=1000000, ratio=2048)", run_inf.Param(1000000)) {
    run(heap, 1000000, 2048);
    context.Cancel();
}

BENCHMARK_FIXTURE(HeapParamFixture<GRon::priority_queue_mfh<int>>, "run(GRon::priority_queue_mfh, n=1000000, ratio=4096)", run_inf.Param(1000000)) {
    run(heap, 1000000, 4096);
    context.Cancel();
}

BENCHMARK_FIXTURE(HeapParamFixture<GRon::priority_queue_mfh<int>>, "run(GRon::priority_queue_mfh, n=1000000, ratio=8192)", run_inf.Param(1000000)) {
    run(heap, 1000000, 8192);
    context.Cancel();
}

BENCHMARK_FIXTURE(HeapParamFixture<GRon::priority_queue_mfh<int>>, "run(GRon::priority_queue_mfh, n=1000000, ratio=16384)", run_inf.Param(1000000)) {
    run(heap, 1000000, 16384);
    context.Cancel();
}

/**
 * std::priority_queue, n=1000000
 */

BENCHMARK_FIXTURE(HeapFixture<std::priority_queue<int>>, "run(std::priority_queue, n=1000000, ratio=512)", run_inf) {
    run(heap, 1000000, 512);
    context.Cancel();
}

BENCHMARK_FIXTURE(HeapFixture<std::priority_queue<int>>, "run(std::priority_queue, n=1000000, ratio=1024)", run_inf) {
    run(heap, 1000000, 1024);
    context.Cancel();
}

BENCHMARK_FIXTURE(HeapFixture<std::priority_queue<int>>, "run(std::priority_queue, n=1000000, ratio=2048)", run_inf) {
    run(heap, 1000000, 2048);
    context.Cancel();
}

BENCHMARK_FIXTURE(HeapFixture<std::priority_queue<int>>, "run(std::priority_queue, n=1000000, ratio=4096)", run_inf) {
    run(heap, 1000000, 4096);
    context.Cancel();
}

BENCHMARK_FIXTURE(HeapFixture<std::priority_queue<int>>, "run(std::priority_queue, n=1000000, ratio=8192)", run_inf) {
    run(heap, 1000000, 8192);
    context.Cancel();
}

BENCHMARK_FIXTURE(HeapFixture<std::priority_queue<int>>, "run(std::priority_queue, n=1000000, ratio=16384)", run_inf) {
    run(heap, 1000000, 16384);
    context.Cancel();
}


BENCHMARK_MAIN()