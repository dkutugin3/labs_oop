cmake_minimum_required(VERSION 3.10)
project(lab1)

set(CMAKE_CXX_STANDARD 14)

find_package(GTest)

add_library(function src/function.cpp)

add_executable(lab1 src/main.cpp)
add_executable(lab1_test test/test.cpp)

target_link_libraries(lab1 function)
target_link_libraries(lab1_test function)


target_link_libraries(lab1_test GTest::gtest GTest::gtest_main)
