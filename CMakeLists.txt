cmake_minimum_required(VERSION 3.10)

# Название проекта
project(ContainerTest)

# Установка стандарта C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Добавление исполняемого файла
add_executable(ContainerTest
    src/main.cpp
)

# Указание директории с заголовочными файлами
target_include_directories(ContainerTest PUBLIC include)