cmake_minimum_required(VERSION 3.10)

# Название проекта
project(FigureProject)

# Установка стандартов C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Включение директорий заголовков
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Добавление исходников приложения
set(SOURCE_FILES
    src/main.cpp
    src/figure.cpp
)

# Создание бинарного файла для основного приложения
add_executable(FigureApp ${SOURCE_FILES})

# Добавление исходников для тестов
set(TEST_FILES
    test/tests.cpp
    src/figure.cpp # Добавляем исходники, чтобы их можно было протестировать
)

# Добавление Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.tar.gz
)
FetchContent_MakeAvailable(googletest)

# Создание бинарного файла для тестов
add_executable(FigureTests ${TEST_FILES})

# Линковка с Google Test
target_link_libraries(FigureTests gtest gtest_main)

# Включение тестирования
enable_testing()

# Автоматическое обнаружение тестов
include(GoogleTest)
gtest_discover_tests(FigureTests)
