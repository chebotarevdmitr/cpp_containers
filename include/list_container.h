#pragma once
#include <stdexcept>
#include <string>

template <typename T>
class ListContainer {
private:
    // Узел списка
    struct Node {
        T data;          // Хранимые данные
        Node* next;      // Указатель на следующий узел
        Node* prev;      // Указатель на предыдущий узел

        // Конструктор узла
        Node(const T& value) 
            : data(value), next(nullptr), prev(nullptr) {}
    };

    Node* head = nullptr; // Первый элемент списка
    Node* tail = nullptr; // Последний элемент списка
    size_t elements_count = 0; // Количество элементов

public:
    // Конструктор по умолчанию
    ListContainer() = default;

    // Деструктор
    ~ListContainer() {
        clear();
    }

    // Добавление в конец
    void push_back(const T& value) {
        Node* new_node = new Node(value);
        if (tail == nullptr) {
            head = tail = new_node;
        } else {
            tail->next = new_node;
            new_node->prev = tail;
            tail = new_node;
        }
        elements_count++;
    }

    // Добавление в начало
    void push_front(const T& value) {
        Node* new_node = new Node(value);
        if (head == nullptr) {
            head = tail = new_node;
        } else {
            head->prev = new_node;
            new_node->next = head;
            head = new_node;
        }
        elements_count++;
    }

    // Количество элементов
    size_t size() const {
        return elements_count;
    }

private:
    // Очистка списка
    void clear() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = tail = nullptr;
        elements_count = 0;
    }
};