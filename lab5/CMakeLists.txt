cmake_minimum_required(VERSION 3.10)
project(DynamicArray)

# Установка стандарта C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Указываем пути к заголовочным файлам
include_directories(include)

# Добавляем исходные файлы
add_executable(DynamicArray
    src/main.cpp
    src/memory.cpp
)

# Указываем дополнительные файлы для шаблонов
target_sources(DynamicArray PRIVATE src/array.tpp)

# Опции для компилятора
target_compile_options(DynamicArray PRIVATE -Wall -Wextra -Wpedantic)
