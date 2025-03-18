#include <gtest/gtest.h>
#include "../include/list_container.h"

// Тест 1: Проверка создания пустого списка
TEST(ListContainer, EmptyOnCreation) {
    ListContainer<int> list;
    EXPECT_TRUE(list.empty());       // Ожидаем, что список пуст
    EXPECT_EQ(list.size(), 0);       // Размер должен быть 0
}

// Тест 2: Добавление элементов в начало и конец
TEST(ListContainer, PushFrontAndBack) {
    ListContainer<int> list;
    list.push_front(10);             // Добавляем 10 в начало
    list.push_back(20);              // Добавляем 20 в конец
    
    EXPECT_EQ(list.size(), 2);       // Размер должен быть 2
    EXPECT_EQ(list.front(), 10);     // Первый элемент = 10
    EXPECT_EQ(list.back(), 20);      // Последний элемент = 20
}

// Тест 3: Удаление элемента из начала
TEST(ListContainer, PopFront) {
    ListContainer<int> list{5, 10, 15}; // Инициализация списка {5, 10, 15}
    list.pop_front();                // Удаляем первый элемент
    
    EXPECT_EQ(list.front(), 10);     // Теперь первый элемент = 10
    EXPECT_EQ(list.size(), 2);       // Размер = 2
}

// Тест 4: Проверка связей между узлами
TEST(ListContainer, NodeLinks) {
    ListContainer<int> list;
    list.push_back(10);              // Список: [10]
    list.push_back(20);              // Список: [10, 20]
    
    ASSERT_NE(list.getHead(), nullptr); // Голова не должна быть nullptr
    ASSERT_NE(list.getTail(), nullptr); // Хвост не должен быть nullptr
    
    EXPECT_EQ(list.getHead()->next, list.getTail()); // head.next указывает на tail
    EXPECT_EQ(list.getTail()->prev, list.getHead()); // tail.prev указывает на head
}

// Тест 5: Проверка перемещения контейнера
TEST(ListContainer, MoveContainer) {
    ListContainer<int> source;
    source.push_back(42);            // Исходный список: [42]
    
    ListContainer<int> dest = std::move(source); // Перемещаем source в dest
    
    EXPECT_TRUE(source.empty());     // Исходный список должен стать пустым
    EXPECT_EQ(dest.front(), 42);     // dest содержит элемент 42
}

// Тест 6: Итерация по элементам списка
TEST(ListContainer, Iteration) {
    ListContainer<int> list{1, 2, 3}; // Список: [1, 2, 3]
    int sum = 0;
    
    for (auto it = list.begin(); it != list.end(); ++it) {
        sum += *it;
    }
    
    EXPECT_EQ(sum, 6);               // 1 + 2 + 3 = 6
}

// Тест 7: Проверка копирования контейнера
TEST(ListContainer, CopyContainer) {
    ListContainer<int> original;
    original.push_back(100);          // Оригинал: [100]
    
    ListContainer<int> copy = original; // Создаем копию
    copy.push_back(200);              // Копия: [100, 200]
    
    EXPECT_EQ(original.size(), 1);    // Оригинал остался без изменений
    EXPECT_EQ(copy.size(), 2);        // Копия содержит два элемента
}

// Тест 8: Проверка деструкторов
TEST(ListContainer, DestructorCalls) {
    struct Trackable {
        static int count;
        Trackable() { count++; }
        ~Trackable() { count--; }
    };
    
    {
        ListContainer<Trackable> list;
        list.push_back(Trackable{});  // Добавляем два элемента
        list.push_back(Trackable{});
        EXPECT_EQ(Trackable::count, 2); // Должно быть 2 объекта
    } // При выходе из блока вызывается деструктор list
    
    EXPECT_EQ(Trackable::count, 0);   // Все объекты уничтожены
}
int Trackable::count = 0;             // Инициализация статической переменной

// Тест 9: Удаление из пустого списка
TEST(ListContainer, PopEmpty) {
    ListContainer<int> list;
    EXPECT_THROW(list.pop_front(), std::out_of_range); // Удаление из пустого списка должно выбрасывать исключение
}

// Тест 10: Проверка доступа к несуществующему элементу
TEST(ListContainer, InvalidAccess) {
    ListContainer<int> list;
    EXPECT_THROW(list.front(), std::out_of_range); // Попытка доступа к front() пустого списка
}