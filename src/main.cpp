#include <iostream>
#include "../include/sequential_container.h"
#include "../include/list_container.h"

// Функция для вывода содержимого SequentialContainer
template <typename T>
void printSequentialContainer(const SequentialContainer<T>& container) {
    for (size_t i = 0; i < container.size(); ++i) {
        std::cout << container.at(i) << " ";
    }
    std::cout << std::endl;
}

// Функция для вывода содержимого ListContainer
template <typename T>
void printListContainer(const ListContainer<T>& container) {
    for (size_t i = 0; i < container.size(); ++i) {
        std::cout << container.at(i) << " ";
    }
    std::cout << std::endl;
}

int main() {
    // Тестирование SequentialContainer
    std::cout << "Testing SequentialContainer:\n";
    SequentialContainer<int> seqContainer;

    // Добавление элементов от 0 до 9
    for (int i = 0; i < 10; ++i) {
        seqContainer.push_back(i);
    }

    std::cout << "Initial SequentialContainer: ";
    printSequentialContainer(seqContainer);

    // Удаление элементов
    seqContainer.erase(2); // Удаляем третий элемент
    seqContainer.erase(3); // Удаляем пятый элемент
    seqContainer.erase(4); // Удаляем седьмой элемент

    std::cout << "After removing elements: ";
    printSequentialContainer(seqContainer);

    // Добавление элементов
    seqContainer.insert(0, 10); // В начало
    seqContainer.insert(seqContainer.size() / 2, 20); // В середину
    seqContainer.push_back(30); // В конец

    std::cout << "Final SequentialContainer: ";
    printSequentialContainer(seqContainer);

    // Тестирование ListContainer
    std::cout << "\nTesting ListContainer:\n";
    ListContainer<int> listContainer;

    // Добавление элементов от 0 до 9
    for (int i = 0; i < 10; ++i) {
        listContainer.push_back(i);
    }

    std::cout << "Initial ListContainer: ";
    printListContainer(listContainer);

    // Удаление элементов
    listContainer.erase(2); // Удаляем третий элемент
    listContainer.erase(3); // Удаляем пятый элемент
    listContainer.erase(4); // Удаляем седьмой элемент

    std::cout << "After removing elements: ";
    printListContainer(listContainer);

    // Добавление элементов
    listContainer.insert(0, 10); // В начало
    listContainer.insert(listContainer.size() / 2, 20); // В середину
    listContainer.push_back(30); // В конец

    std::cout << "Final ListContainer: ";
    printListContainer(listContainer);

    return 0;
}