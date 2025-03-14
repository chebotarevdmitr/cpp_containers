#pragma once //
#include <stdexcept>  // Для исключений
#include <string>     // Для std::to_string

template <typename T>  // Шаблонный класс
class SequentialContainer {
public:
    // 1. Конструкторы и деструктор
    SequentialContainer();             // Конструктор по умолчанию
    ~SequentialContainer();            // Деструктор

    // 2. Основные методы
    void push_back(const T& value);    // Добавление элемента в конец
    size_t size() const;               // Текущее количество элементов
    T& at(size_t index);               // Доступ с проверкой индекса
    const T& at(size_t index) const;   // Константная версия

private:
    T* data = nullptr;                   // Динамический массив элементов
    size_t elements_count = 0;           // Фактическое количество элементов
    size_t current_capacity = 0;         // Выделенная память

    void resize_if_needed();             // Вспомогательный метод для изменения ёмкости
};

// ----------------- Реализации методов -----------------

// Конструктор по умолчанию
template <typename T>
SequentialContainer<T>::SequentialContainer() = default;

// Деструктор
template <typename T>
SequentialContainer<T>::~SequentialContainer() {
    delete[] data;  // Освобождаем память
}

// Текущее количество элементов
template <typename T>
size_t SequentialContainer<T>::size() const {
    return elements_count;
}

// Добавление элемента в конец
template <typename T>
void SequentialContainer<T>::push_back(const T& value) {
    resize_if_needed();                   // Увеличиваем ёмкость при необходимости
    data[elements_count] = value;       // Добавляем элемент
    elements_count++;                  // Увеличиваем счётчик
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
    return const_cast<SequentialContainer*>(this)->at(index); // Используем не-const версию
}

// Вспомогательный метод для изменения ёмкости
template <typename T>
void SequentialContainer<T>::resize_if_needed() {
    if (elements_count == current_capacity) {
        size_t new_capacity = (current_capacity == 0) ? 1 : current_capacity * 2;
        T* new_data = new T[new_capacity];

        // Копируем элементы из старого массива
        for (size_t i = 0; i < elements_count; ++i) {
            new_data[i] = data[i];
        }

        delete[] data;      // Освобождаем старую память
        data = new_data;    // Переключаем указатель
        current_capacity = new_capacity;
    }
}