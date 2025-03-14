find_package(GTest REQUIRED)

# Тесты для vector
add_executable(vector_tests vector_tests.cpp)
target_link_libraries(vector_tests GTest::GTest GTest::Main)

# Тесты для list
add_executable(list_tests list_tests.cpp)
target_link_libraries(list_tests GTest::GTest GTest::Main)
