#pragma once          // Защита от двойного включения
#include <stdexcept>  // Для исключений
#include <string>     // Для std::to_string
#include <algorithm>  // Для std::copy
// Шаблонный класс для последовательного контейнера
template <typename T>  // T - тип хранимых элементов
class SequentialContainer {  // Класс-контейнер
public:
    // Конструкторы и деструктор
    SequentialContainer() = default;  // Конструктор по умолчанию
    ~SequentialContainer();           // Деструктор

    // Конструктор копирования
    SequentialContainer(const SequentialContainer& other); // Копирование
    // Оператор присваивания копированием
    SequentialContainer& operator=(const SequentialContainer& other);// Присваивание

    // Конструктор перемещения
    SequentialContainer(SequentialContainer&& other) noexcept;// Перемещение
    // Оператор присваивания перемещением
    SequentialContainer& operator=(SequentialContainer&& other) noexcept;// Присваивание

    // Основные методы
    void push_back(const T& value);       // Добавление элемента в конец
    void pop_back();                      // Удаление последнего элемента
    // Текущее количество элементов
    bool empty() const { return elements_count == 0; }  // Проверка на пустоту
    size_t size() const;                                // Текущее количество элементов
    void clear();                         // Очистка контейнера
    void reserve(size_t new_capacity);    // Зарезервировать память

    // Доступ к элементам
    T& at(size_t index);                  // Доступ с проверкой индекса
    const T& at(size_t index) const;      // Константная версия

private:
    T* data = nullptr;           // Динамический массив элементов
    size_t elements_count = 0;   // Фактическое количество элементов
    size_t current_capacity = 0; // Выделенная память

    void resize_if_needed();      // Вспомогательный метод для изменения ёмкости
};

// ----------------- Реализации методов -----------------

// Деструктор
template <typename T>
SequentialContainer<T>::~SequentialContainer() {
    delete[] data;  // Освобождаем память
}

// Конструктор копирования
template <typename T>
SequentialContainer<T>::SequentialContainer(const SequentialContainer& other)
    : elements_count(other.elements_count), current_capacity(other.current_capacity) {
    if (current_capacity > 0) {
        data = new T[current_capacity];
        std::copy(other.data, other.data + elements_count, data);
    }
}

// Оператор присваивания копированием
template <typename T>
SequentialContainer<T>& SequentialContainer<T>::operator=(const SequentialContainer& other) {
    if (this != &other) {
        delete[] data;  // Освобождаем старую память
        elements_count = other.elements_count;
        current_capacity = other.current_capacity;
        if (current_capacity > 0) {
            data = new T[current_capacity];
            std::copy(other.data, other.data + elements_count, data);
        } else {
            data = nullptr;
        }
    }
    return *this;
}

// Конструктор перемещения
template <typename T>
SequentialContainer<T>::SequentialContainer(SequentialContainer&& other) noexcept
    : data(other.data), elements_count(other.elements_count), current_capacity(other.current_capacity) {
    other.data = nullptr;
    other.elements_count = 0;
    other.current_capacity = 0;
}

// Оператор присваивания перемещением
template <typename T>
SequentialContainer<T>& SequentialContainer<T>::operator=(SequentialContainer&& other) noexcept {
    if (this != &other) {
        delete[] data;  // Освобождаем старую память
        data = other.data;
        elements_count = other.elements_count;
        current_capacity = other.current_capacity;

        other.data = nullptr;
        other.elements_count = 0;
        other.current_capacity = 0;
    }
    return *this;
}

// Текущее количество элементов
template <typename T>
size_t SequentialContainer<T>::size() const {
    return elements_count;
}

// Добавление элемента в конец
template <typename T>
void SequentialContainer<T>::push_back(const T& value) {
    resize_if_needed();         // Увеличиваем ёмкость при необходимости
    data[elements_count++] = value; // Добавляем элемент и увеличиваем счётчик
}

// Удаление последнего элемента
template <typename T>
void SequentialContainer<T>::pop_back() {
    if (elements_count == 0) {
        throw std::out_of_range("Cannot pop_back from an empty container");
    }
    --elements_count;
}

// Очистка контейнера
template <typename T>
void SequentialContainer<T>::clear() {
    delete[] data;
    data = nullptr;
    elements_count = 0;
    current_capacity = 0;
}

// Зарезервировать память
template <typename T>
void SequentialContainer<T>::reserve(size_t new_capacity) {
    if (new_capacity > current_capacity) {
        T* new_data = new T[new_capacity];
        std::copy(data, data + elements_count, new_data);
        delete[] data;
        data = new_data;
        current_capacity = new_capacity;
    }
}

// Доступ к элементу с проверкой индекса
template <typename T>
T& SequentialContainer<T>::at(size_t index) {
    if (index >= elements_count) {
        throw std::out_of_range("Index " + std::to_string(index) +
                                " is out of bounds (size = " +
                                std::to_string(elements_count) + ")");
    }
    return data[index];
}

// Константная версия at()
template <typename T>
const T& SequentialContainer<T>::at(size_t index) const {
    if (index >= elements_count) {
        throw std::out_of_range("Index " + std::to_string(index) +
                                " is out of bounds (size = " +
                                std::to_string(elements_count) + ")");
    }
    return data[index];
}

// Вспомогательный метод для изменения ёмкости
template <typename T>
void SequentialContainer<T>::resize_if_needed() {
    if (elements_count == current_capacity) {
        size_t new_capacity = (current_capacity == 0) ? 1 : current_capacity * 2;
        T* new_data = new T[new_capacity];
        std::copy(data, data + elements_count, new_data);
        delete[] data;
        data = new_data;
        current_capacity = new_capacity;
    }
}
//end{minted}
//
//     std::vector — стандартный контейнер C++.
//     Правило трёх/пяти/нуля — управление ресурсами в C++.
//     std::copy — копирование элементов.
//     Исключения в C++ — обработка ошибок.
//