cmake_minimum_required(VERSION 3.10)
project(Lab5)

set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)
find_package(benchmark REQUIRED)

add_library(lab_logic dsu.c list.c graph.c)

# add_executable(run_tests gtest-lab5.cpp)
# target_link_libraries(run_tests GTest::gtest_main lab_logic)

# add_executable(run_bench bench-lab5.cpp)
# target_link_libraries(run_bench benchmark::benchmark lab_logic)

add_executable(run_lab lab5.c)
target_link_libraries(run_lab lab_logic)
