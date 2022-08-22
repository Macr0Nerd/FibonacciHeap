cmake_minimum_required(VERSION 3.21)
cmake_policy(SET CMP0077 NEW)
cmake_policy(SET CMP0126 NEW)

project(HeapBenchmark VERSION 0.0.0 LANGUAGES CXX)

find_package(FibonacciHeap 2.0.0 REQUIRED)

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/extern/CppBenchmark/CMakeLists.txt")
    message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

add_subdirectory(extern/CppBenchmark)

set(BENCHMARK_TYPE "INT" CACHE STRING "Set the benchmark to run (INT or STR)")

add_executable(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} PRIVATE GRon::FibonacciHeap)
target_link_libraries(${PROJECT_NAME} PUBLIC cppbenchmark)

set_target_properties(${PROJECT_NAME} PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
        PREFIX ""
        )

target_include_directories(${PROJECT_NAME}
        INTERFACE
        $<INSTALL_INTERFACE:include/>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        )

if(${BENCHMARK_TYPE} STREQUAL "INT")
    target_sources(${PROJECT_NAME}
            PUBLIC
            app/int.cpp
    )
elseif(${BENCHMARK_TYPE} STREQUAL "STR")
    target_sources(${PROJECT_NAME}
            PUBLIC
            app/string.cpp)
endif()