#include <iostream>
#include "../include/sequential_container.h"
#include "../include/list_container.h"

int main() {
    // Тестируем SequentialContainer
    SequentialContainer<int> vec;
    vec.push_back(10);
    vec.push_back(20);
    std::cout << "Vector size: " << vec.size() << std::endl; // 2

    // Тестируем ListContainer
    ListContainer<int> list;
    list.push_back(30);
    list.push_front(40);
    std::cout << "List size: " << list.size() << std::endl; // 2

    return 0;
}