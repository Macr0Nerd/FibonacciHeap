add_executable(${PROJECT_NAME}_tests tests.cpp)
target_link_libraries(${PROJECT_NAME}_tests PRIVATE GRon::FibonacciHeap)
target_link_libraries(${PROJECT_NAME}_tests PRIVATE Catch2::Catch2WithMain)

set_target_properties(${PROJECT_NAME}_tests PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
        PREFIX ""
        )

catch_discover_tests(${PROJECT_NAME}_tests)