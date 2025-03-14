find_package(GTest REQUIRED          )# Поиск библиотеки GTest

# Тесты для vector (последовательный контейнер)
add_executable(containers_tests       # Создание исполняемого файла
    vector_tests.cpp                  # Добавление исходного файла
    list_tests.cpp                    # Добавление исходного файла
)
# Подключение библиотеки GTest
target_link_libraries(containers_tests # Цель для подключения библиотек
    GTest::GTest                       # Подключение библиотеки GTest
    GTest::Main                         # Подключение библиотеки GTest
)