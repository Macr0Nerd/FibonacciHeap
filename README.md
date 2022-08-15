# Fibonacci Heap

##### Jump To
* [Requirements](#requirements)
* [Usage](#usage)
* [API](#api)
* [Building](#building)
* [License](#license)

A fibonacci heap is a data structure best used for applications such as priority queues.
What they allow is for is `get_minimum`, `pop_minimum`, and `alter_key` to run in constant time.
Likewise, `get_minimum` will run in logarithmic time (amortized).
For further explanations as to what this means, please watch [the video this project was based upon](https://youtu.be/6JxvKfSV9Ns).

## Requirements
* C++20 (`concepts` & `compare`)
* CMake 3.20 or greater
* CTest

## Usage
This project is designed with Modern CMake principals in mind, so it can easily be used with other CMake projects.
Either install or otherwise link the project, and add:

```cmake
find_package(FibonacciHeap 1.0.0 REQUIRED)
# Add Targets
target_link_libraries(foo PRIVATE GRon::FibonacciHeap)
```

## API
The API for the Fibonacci Heap is quite simple:

* `FibonacciHeap<std::three_way_comparable T>`
  * Creates a Fibonacci Heap object with the provided key type T.
  T **must** be `three_way_comparable`, hence the notation above.

  * `Node`
    * The format the data in the heap is stored in.
    * `T key`
      * Key held by the node
    * `Node* parent`
      * The parent node
    * `std::vector<Node*> children`
      * The child nodes
  * `void insert(T key)`
    * Emplaces a key at the back of the `root_list` vector

  * `Node* get_minimum()`
    * Returns a pointer to the node with the lowest key
    * Also cleans up the heap, allowing `insert()`, `pop_minimum()`, and `alter_key()` to run in constant time.
      Should be called relatively frequently for best results, but the first call after using the other functions may be slower.
      However, once the heap is ordered, this runs in constant time as well.

  * `Node pop_minimum()`
    * Pops off the minimum node and returns the entire node
    * Makes a call to `get_minimum`, so the same distinctions apply

  * `void alter_key(T key, T new_key)`
    * Updates the node containing `key` to now hold `new_key`]
    * Can be combined with `pop_minimum` to remove keys from the heap

## Building
1. Clone the source code

    ```bash
    git clone https://github.com/Macr0Nerd/FibonacciHeap.git
    ```

2. Change directory into the project and create an output directory

    ```bash
    cd FibonacciHeap/
    mkdir build
    ```

3. Generate Makefiles *(if using Ninja, add `-GNinja`)*

    ```bash
    cmake -DCMAKE_BUILD_TYPE=Release -H. -Bbuild
    ```

4. Build project

    ```bash
    cmake --build build/ --config RELEASE
    ```
   
5. Install the project. Examples for Ninja and Make have been provided

    ```bash
    cd build
    make install
    ninja install
    ```

6. (Optional) Run tests

    ```bash
    cd build
    ctest -C RELEASE
    ```

## License
Copyright 2022 Gabriele A. Ron

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

***

This class contains the Catch2 Testing Library from Catch Org which is licensed under the [Boost License](https://opensource.org/licenses/BSL-1.0). Copyright © 2012-2022 [Catch Org](https://github.com/catchorg)