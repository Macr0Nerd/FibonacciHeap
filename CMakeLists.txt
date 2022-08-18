cmake_minimum_required(VERSION 3.20)
project(FibonacciHeap VERSION 1.0.0 LANGUAGES CXX)

################
# Dependencies #
################

find_package(Catch2 3 QUIET)
if(NOT Catch2_FOUND)
    message(STATUS "Catch2 not found, fetching")
    Include(FetchContent)

    FetchContent_Declare(
            Catch2
            GIT_REPOSITORY https://github.com/catchorg/Catch2.git
            GIT_TAG        v3.1.0
    )

    FetchContent_MakeAvailable(Catch2)
    list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
endif()

find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/../.git")
    # Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

#################################
# This is to create the library #
#################################

add_library(${PROJECT_NAME} INTERFACE)
add_library(GRon::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

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

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(CTest)
    include(Catch)
endif ()

##########################
# Set optimization flags #
##########################

if (NOT CMAKE_CXX_FLAGS)
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        if (MSVC)
            list(APPEND CMAKE_CXX_FLAGS "/O0")
        else ()
            list(APPEND CMAKE_CXX_FLAGS "-O0")
        endif ()
    else ()
        if (MSVC)
            list(APPEND CMAKE_CXX_FLAGS "/O3")
        else ()
            list(APPEND CMAKE_CXX_FLAGS "-O3")
        endif ()
    endif ()
    message("Setting CXX flags to default for ${CMAKE_BUILD_TYPE} mode (${CMAKE_CXX_FLAGS})")
else ()
    message("CXX flags are already set to ${CMAKE_CXX_FLAGS}")
endif ()

##########################
# Installing the library #
##########################

include(GNUInstallDirs)
set(INSTALL_CONFIG_DIR ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})

install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}Targets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        )

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
        ${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion
        ARCH_INDEPENDENT
)
configure_package_config_file(
        ${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in
        ${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
        INSTALL_DESTINATION ${INSTALL_CONFIG_DIR}
)

install(EXPORT ${PROJECT_NAME}Targets
        FILE ${PROJECT_NAME}Targets.cmake
        NAMESPACE GRon::
        DESTINATION ${INSTALL_CONFIG_DIR}
        )

install(FILES
        ${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
        ${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
        DESTINATION ${INSTALL_CONFIG_DIR}
        )

install(DIRECTORY include/GRon DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

export(
        EXPORT ${PROJECT_NAME}Targets
        NAMESPACE GRon::
        FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}Targets.cmake
)

set(CMAKE_EXPORT_PACKAGE_REGISTRY ON)
export(PACKAGE ${PROJECT_NAME})

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
    add_subdirectory(tests)
endif ()