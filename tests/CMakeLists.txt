Include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.1.0
)

FetchContent_MakeAvailable(Catch2)

add_executable(${PROJECT_NAME}_tests tests.cpp)
target_link_libraries(${PROJECT_NAME}_tests PRIVATE GRon::FibonacciHeap)
target_link_libraries(${PROJECT_NAME}_tests PRIVATE Catch2::Catch2WithMain)

set_target_properties(${PROJECT_NAME}_tests PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
        PREFIX ""
        )

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)
catch_discover_tests(${PROJECT_NAME}_tests)