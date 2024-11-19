cmake_minimum_required(VERSION 3.10)

# Указываем название проекта
project(FigureProject)

# Указываем стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Указываем директорию с заголовочными файлами
include_directories(include)

# Добавляем исполнимый файл (будет собираться только main)
add_executable(main
    src/main.cpp
    src/figure.cpp
)