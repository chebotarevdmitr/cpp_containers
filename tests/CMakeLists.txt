find_package(GTest REQUIRED)

# Основной исполняемый файл для всех тестов
add_executable(containers_tests
    vector_tests.cpp
    list_tests.cpp
)

target_link_libraries(containers_tests
    GTest::GTest 
    GTest::Main
)