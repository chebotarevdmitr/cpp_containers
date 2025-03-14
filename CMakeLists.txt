cmake_minimum_required(VERSION 3.10)# Проверка версии CMake.
# Если версия установленной программы старее указанной, произойдёт аварийное завершение работы CMake.
project(cpp_containers)# Название проекта

set(CMAKE_CXX_STANDARD 17)# Устанавливаем стандарт языка C++17
set(CMAKE_CXX_STANDARD_REQUIRED ON)# Требуем явно указывать стандарт языка

# Основная программа
add_executable(main_app src/main.cpp)# Создает исполняемый файл main_app из исходника main.cpp

# Подключаем тесты
add_subdirectory(tests)# Добавляем каталог tests в проект