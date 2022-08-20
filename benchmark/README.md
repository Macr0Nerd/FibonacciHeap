# Fibonacci Heap Benchmarks
These benchmarks are used to test the speed of the Fibonacci Heap implemented into a priority queue and tests it against std::priority_queue.

## Building
First set up the external dependency `CppBenchmark` in `extern` (it's a git submodule so I can't automate the building of it, sorry), and then build the benchmarks in the same way as with the main project.
Refer to [CppBenchmark](https://github.com/chronoxor/CppBenchmark) for more info on how the benchmarks work.

## Set Benchmark Type
When you run the first cmake command, run it with:

    -DBENCHMARK_TYPE=TYPE

where `TYPE` is either:
* INT
* STR
