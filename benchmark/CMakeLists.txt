cmake_minimum_required(VERSION 3.20)
project(HeapBenchmark VERSION 0.0.0 LANGUAGES CXX)

find_package(phmap REQUIRED)
find_package(FibonacciHeap 1.0.0 REQUIRED)

add_executable(${PROJECT_NAME} app/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE GRon::FibonacciHeap)

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/extern/CppBenchmark/CMakeLists.txt")
    message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

add_subdirectory(extern/CppBenchmark)
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


