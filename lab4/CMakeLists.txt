cmake_minimum_required(VERSION 3.10)
project(Lab4_Tests)

set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)
find_package(benchmark REQUIRED)

add_library(lab_logic avl-tree.c)

add_executable(run_tests gtest-lab4.cpp)
target_link_libraries(run_tests GTest::gtest_main lab_logic)

add_executable(run_bench bench-lab4.cpp)
target_link_libraries(run_bench benchmark::benchmark lab_logic)
