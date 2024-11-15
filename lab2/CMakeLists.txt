cmake_minimum_required(VERSION 3.10)
project(lab2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(Money src/Money.cpp)
add_executable(runTests test/test.cpp)
target_link_libraries(runTests Money gtest gtest_main)

add_executable(main src/main.cpp src/Money.cpp)

# find_package(GTest REQUIRED)
# add_executable(hex_tests test/hex_test.cpp src/Hexad.cpp)

# Линкуем Google Test
# target_link_libraries(hex_tests GTest::GTest GTest::Main pthread)

# enable_testing()
# add_test(NAME HexadUnitTests COMMAND hex_tests)