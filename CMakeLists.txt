# Built by:
# Harshitapreet Kaur (https://github.com/Harshita1204) (harshitak1204@gmail.com)
# Pranav Sinha (https://github.com/Penguin5681) (pranavsinha922@gmail.com)
# 
# Licensed under the MIT License.

cmake_minimum_required(VERSION 3.20)
if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()
project(math_core LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(DEFINED ENV{VCPKG_ROOT})
    set(CMAKE_TOOLCHAIN_FILE
        "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "")
endif()

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE) 

FetchContent_MakeAvailable(googletest)

add_library(math_core STATIC
    src/context.cpp
    src/lexer.cpp
    src/parser.cpp
    src/evaluator.cpp
    src/symbolic.cpp
    src/solver.cpp
    src/formatter.cpp
)

target_include_directories(math_core
    PUBLIC  include       
    PRIVATE src           
)

enable_testing()

add_executable(math_core_tests
    tests/test_lexer.cpp
    tests/test_parser.cpp
    tests/test_evaluator.cpp
    tests/test_symbolic.cpp
)

target_link_libraries(math_core_tests PRIVATE
    math_core
    GTest::gtest
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(math_core_tests)