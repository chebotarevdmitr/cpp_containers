# Подключение Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Добавление исполняемого файла для тестов
add_executable(containers_tests
    vector_tests.cpp
    list_tests.cpp
)

# Связывание с библиотекой Google Test
target_link_libraries(containers_tests ${GTEST_BOTH_LIBRARIES} pthread)

# Указание директории с заголовочными файлами
target_include_directories(containers_tests PRIVATE ../include)