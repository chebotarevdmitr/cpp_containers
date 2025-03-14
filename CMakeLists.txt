cmake_minimum_required(VERSION 3.10)
project(cpp_containers)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Подключаем заголовки из include
include_directories(include)

# Основное приложение
add_executable(main_app src/main.cpp)

# Подключаем тесты
add_subdirectory(tests)
