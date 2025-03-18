#include <gtest/gtest.h>
#include "../include/list_container.h"

// Тест создания контейнера
TEST(ListContainer, Creation) {
    ListContainer<int> container;
    EXPECT_EQ(container.size(), 0); // Проверяем, что размер равен 0
    EXPECT_TRUE(container.empty()); // Проверяем, что контейнер пуст
}

// Тест добавления элементов
TEST(ListContainer, PushBack) {
    ListContainer<int> container;
    container.push_back(10);
    container.push_back(20);
    EXPECT_EQ(container.size(), 2); // Проверяем размер
    EXPECT_EQ(container.at(0), 10); // Проверяем первый элемент
    EXPECT_EQ(container.at(1), 20); // Проверяем второй элемент
}

// Тест удаления последнего элемента
TEST(ListContainer, PopBack) {
    ListContainer<int> container;
    container.push_back(10);
    container.push_back(20);
    container.pop_back();
    EXPECT_EQ(container.size(), 1); // Проверяем размер
    EXPECT_EQ(container.at(0), 10); // Проверяем оставшийся элемент
}

// Тест вставки элемента
TEST(ListContainer, Insert) {
    ListContainer<int> container;
    container.push_back(10);
    container.push_back(30);
    container.insert(1, 20); // Вставляем 20 между 10 и 30
    EXPECT_EQ(container.size(), 3); // Проверяем размер
    EXPECT_EQ(container.at(0), 10); // Проверяем первый элемент
    EXPECT_EQ(container.at(1), 20); // Проверяем вставленный элемент
    EXPECT_EQ(container.at(2), 30); // Проверяем последний элемент
}

// Тест удаления элемента по индексу
TEST(ListContainer, Erase) {
    ListContainer<int> container;
    container.push_back(10);
    container.push_back(20);
    container.push_back(30);
    container.erase(1); // Удаляем элемент с индексом 1 (20)
    EXPECT_EQ(container.size(), 2); // Проверяем размер
    EXPECT_EQ(container.at(0), 10); // Проверяем первый элемент
    EXPECT_EQ(container.at(1), 30); // Проверяем последний элемент
}

// Тест исключения при доступе к несуществующему элементу
TEST(ListContainer, OutOfRangeException) {
    ListContainer<int> container;
    EXPECT_THROW(container.at(0), std::out_of_range); // Проверяем выброс исключения
}

// Тест очистки контейнера
TEST(ListContainer, Clear) {
    ListContainer<int> container;
    container.push_back(10);
    container.push_back(20);
    container.clear();
    EXPECT_EQ(container.size(), 0); // Проверяем, что размер равен 0
    EXPECT_TRUE(container.empty()); // Проверяем, что контейнер пуст
}