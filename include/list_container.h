#pragma once // Защита от повторного включения

#include <stdexcept>  // Для обработки исключений (например, std::out_of_range)
#include <string>     // Для преобразования чисел в строки при выводе ошибок

// Узел списка
template <typename T>
struct ListNode {
    T value;            // Значение узла
    ListNode* prev;     // Указатель на предыдущий узел
    ListNode* next;     // Указатель на следующий узел

    // Конструктор узла
    explicit ListNode(const T& val = T(), ListNode* prv = nullptr, ListNode* nxt = nullptr)
        : value(val), prev(prv), next(nxt) {}
};

// Класс контейнера на основе двусвязного списка
template <typename T>
class ListContainer {
private:
    ListNode<T>* head;  // Указатель на голову списка
    ListNode<T>* tail;  // Указатель на хвост списка
    size_t count;       // Количество элементов в списке

public:
    // Конструктор по умолчанию
    ListContainer() : head(nullptr), tail(nullptr), count(0) {}

    // Деструктор
    ~ListContainer() {
        clear(); // Освобождаем память всех узлов
    }

    // Конструктор копирования
    ListContainer(const ListContainer& other) : head(nullptr), tail(nullptr), count(0) {
        for (ListNode<T>* current = other.head; current != nullptr; current = current->next) {
            push_back(current->value); // Копируем элементы
        }
    }

    // Оператор присваивания копированием
    ListContainer& operator=(const ListContainer& other) {
        if (this != &other) {
            clear(); // Очищаем текущий список
            for (ListNode<T>* current = other.head; current != nullptr; current = current->next) {
                push_back(current->value); // Копируем элементы
            }
        }
        return *this;
    }

    // Конструктор перемещения
    ListContainer(ListContainer&& other) noexcept
        : head(other.head), tail(other.tail), count(other.count) {
        other.head = other.tail = nullptr;
        other.count = 0;
    }

    // Оператор присваивания перемещением
    ListContainer& operator=(ListContainer&& other) noexcept {
        if (this != &other) {
            clear(); // Очищаем текущий список
            head = other.head;
            tail = other.tail;
            count = other.count;
            other.head = other.tail = nullptr;
            other.count = 0;
        }
        return *this;
    }

    // Метод добавления элемента в конец
    void push_back(const T& value) {
        ListNode<T>* newNode = new ListNode<T>(value, tail, nullptr);
        if (tail) {
            tail->next = newNode; // Если список не пустой, связываем хвост с новым узлом
        } else {
            head = newNode; // Если список пустой, новый узел становится головой
        }
        tail = newNode; // Новый узел становится хвостом
        ++count;
    }

    // Метод добавления элемента в начало
    void push_front(const T& value) {
        ListNode<T>* newNode = new ListNode<T>(value, nullptr, head);
        if (head) {
            head->prev = newNode; // Если список не пустой, связываем голову с новым узлом
        } else {
            tail = newNode; // Если список пустой, новый узел становится хвостом
        }
        head = newNode; // Новый узел становится головой
        ++count;
    }

    // Метод удаления последнего элемента
    void pop_back() {
        if (empty()) {
            throw std::out_of_range("Cannot pop_back from an empty container");
        }
        ListNode<T>* toDelete = tail;
        tail = tail->prev; // Перемещаем хвост на предыдущий узел
        if (tail) {
            tail->next = nullptr; // Обнуляем указатель на следующий узел
        } else {
            head = nullptr; // Если список становится пустым, обнуляем голову
        }
        delete toDelete;
        --count;
    }

    // Метод удаления первого элемента
    void pop_front() {
        if (empty()) {
            throw std::out_of_range("Cannot pop_front from an empty container");
        }
        ListNode<T>* toDelete = head;
        head = head->next; // Перемещаем голову на следующий узел
        if (head) {
            head->prev = nullptr; // Обнуляем указатель на предыдущий узел
        } else {
            tail = nullptr; // Если список становится пустым, обнуляем хвост
        }
        delete toDelete;
        --count;
    }

    // Метод вставки элемента по индексу
    void insert(size_t index, const T& value) {
        if (index > count) {
            throw std::out_of_range("Insert index out of range");
        }
        if (index == 0) {
            push_front(value); // Вставка в начало
        } else if (index == count) {
            push_back(value); // Вставка в конец
        } else {
            ListNode<T>* current = getNodeAt(index); // Находим узел по индексу
            ListNode<T>* newNode = new ListNode<T>(value, current->prev, current);
            current->prev->next = newNode;
            current->prev = newNode;
            ++count;
        }
    }

    // Метод удаления элемента по индексу
    void erase(size_t index) {
        if (index >= count) {
            throw std::out_of_range("Erase index out of range");
        }
        if (index == 0) {
            pop_front(); // Удаление из начала
        } else if (index == count - 1) {
            pop_back(); // Удаление из конца
        } else {
            ListNode<T>* toDelete = getNodeAt(index); // Находим узел по индексу
            toDelete->prev->next = toDelete->next;
            toDelete->next->prev = toDelete->prev;
            delete toDelete;
            --count;
        }
    }

    // Метод доступа к элементу по индексу
    T& at(size_t index) {
        ListNode<T>* node = getNodeAt(index);
        return node->value;
    }

    // Константная версия метода at
    const T& at(size_t index) const {
        ListNode<T>* node = getNodeAt(index);
        return node->value;
    }

    // Метод проверки, является ли список пустым
    bool empty() const {
        return count == 0;
    }

    // Метод получения количества элементов
    size_t size() const {
        return count;
    }

    // Метод очистки списка
    void clear() {
        while (!empty()) {
            pop_front(); // Удаляем элементы с начала
        }
    }

private:
    // Вспомогательный метод для получения узла по индексу
    ListNode<T>* getNodeAt(size_t index) const {
        if (index >= count) {
            throw std::out_of_range("Index " + std::to_string(index) + " is out of bounds");
        }
        ListNode<T>* current = head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        return current;
    }
};