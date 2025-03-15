#pragma once
#include <stdexcept>
#include <string>

template <typename T>
class ListContainer {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;

        Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
    };

    Node* head = nullptr;
    Node* tail = nullptr;
    size_t elements_count = 0;

public:
    // Конструктор по умолчанию
    ListContainer() = default;

    // Конструктор копирования
    ListContainer(const ListContainer& other) {
        copy_nodes(other);
    }

    // Оператор присваивания копированием
    ListContainer& operator=(const ListContainer& other) {
        if (this != &other) {
            clear();
            copy_nodes(other);
        }
        return *this;
    }

    // Конструктор перемещения
    ListContainer(ListContainer&& other) noexcept {
        move_nodes(std::move(other));
    }

    // Оператор присваивания перемещением
    ListContainer& operator=(ListContainer&& other) noexcept {
        if (this != &other) {
            clear();
            move_nodes(std::move(other));
        }
        return *this;
    }

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

    // Удаление последнего элемента
    void pop_back() {
        if (empty()) {
            throw std::out_of_range("Cannot pop_back from an empty list");
        }
        Node* to_delete = tail;
        tail = tail->prev;
        if (tail) {
            tail->next = nullptr;
        } else {
            head = nullptr; // Список становится пустым
        }
        delete to_delete;
        elements_count--;
    }

    // Удаление первого элемента
    void pop_front() {
        if (empty()) {
            throw std::out_of_range("Cannot pop_front from an empty list");
        }
        Node* to_delete = head;
        head = head->next;
        if (head) {
            head->prev = nullptr;
        } else {
            tail = nullptr; // Список становится пустым
        }
        delete to_delete;
        elements_count--;
    }

    // Проверка на пустоту
    bool empty() const {
        return elements_count == 0;
    }

    // Количество элементов
    size_t size() const {
        return elements_count;
    }

private:
    // Вспомогательный метод для глубокого копирования
    void copy_nodes(const ListContainer& other) {
        Node* current = other.head;
        while (current != nullptr) {
            push_back(current->data);
            current = current->next;
        }
    }

    // Вспомогательный метод для перемещения ресурсов
    void move_nodes(ListContainer&& other) noexcept {
        head = other.head;
        tail = other.tail;
        elements_count = other.elements_count;
        other.head = other.tail = nullptr;
        other.elements_count = 0;
    }

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