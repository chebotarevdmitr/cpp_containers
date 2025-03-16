#pragma once // Защита от двойного включения заголовочного файла

#include <stdexcept>  // Для обработки исключений (например, std::out_of_range)
#include <string>     // Для преобразования чисел в строки при выводе ошибок
#include <algorithm>  // Для использования std::copy и std::copy_backward

// Шаблонный класс SequentialContainer для создания последовательных контейнеров
template <typename T> // T - тип элементов, которые будут храниться в контейнере
class SequentialContainer {
private:
    T* data = nullptr;           // Указатель на динамический массив для хранения элементов
    size_t elements_count = 0;   // Текущее количество элементов в контейнере
    size_t current_capacity = 0; // Текущая ёмкость контейнера (выделенная память)

    // Вспомогательный метод для увеличения ёмкости контейнера при необходимости
    void resize_if_needed() {
        if (elements_count == current_capacity) { // Если текущая ёмкость исчерпана
            size_t new_capacity = current_capacity == 0 ? 1 : current_capacity * 2; // Увеличиваем ёмкость в 2 раза
            T* new_data = new T[new_capacity]; // Создаем новый массив с новой ёмкостью
            std::copy(data, data + elements_count, new_data); // Копируем старые данные в новый массив
            delete[] data; // Освобождаем старую память
            data = new_data; // Обновляем указатель на новый массив
            current_capacity = new_capacity; // Обновляем значение ёмкости
        }
    }

public:
    // Конструктор по умолчанию
    SequentialContainer() = default;

    // Деструктор для освобождения выделенной памяти
    ~SequentialContainer() {
        delete[] data; // Освобождаем память, выделенную под массив
    }

    // Конструктор копирования для создания копии контейнера
    SequentialContainer(const SequentialContainer& other)
        : elements_count(other.elements_count), current_capacity(other.current_capacity) {
        if (current_capacity > 0) { // Если у оригинала есть выделенная память
            data = new T[current_capacity]; // Выделяем новую память
            std::copy(other.data, other.data + elements_count, data); // Копируем элементы
        }
    }

    // Оператор присваивания копированием
    SequentialContainer& operator=(const SequentialContainer& other) {
        if (this != &other) { // Проверяем, что не присваиваем самому себе
            delete[] data; // Освобождаем старую память
            elements_count = other.elements_count;
            current_capacity = other.current_capacity;
            if (current_capacity > 0) { // Если у оригинала есть выделенная память
                data = new T[current_capacity]; // Выделяем новую память
                std::copy(other.data, other.data + elements_count, data); // Копируем элементы
            } else {
                data = nullptr; // Если оригинальный контейнер пуст, обнуляем указатель
            }
        }
        return *this;
    }

    // Конструктор перемещения для эффективного переноса ресурсов
    SequentialContainer(SequentialContainer&& other) noexcept
        : data(other.data), elements_count(other.elements_count), current_capacity(other.current_capacity) {
        other.data = nullptr; // Обнуляем указатель оригинала
        other.elements_count = other.current_capacity = 0; // Сбрасываем размер и ёмкость оригинала
    }

    // Оператор присваивания перемещением
    SequentialContainer& operator=(SequentialContainer&& other) noexcept {
        if (this != &other) { // Проверяем, что не присваиваем самому себе
            delete[] data; // Освобождаем старую память
            data = other.data; // Переносим указатель на данные
            elements_count = other.elements_count;
            current_capacity = other.current_capacity;
            other.data = nullptr; // Обнуляем указатель оригинала
            other.elements_count = other.current_capacity = 0; // Сбрасываем размер и ёмкость оригинала
        }
        return *this;
    }

    // Метод добавления элемента в конец контейнера
    void push_back(const T& value) {
        resize_if_needed(); // Увеличиваем ёмкость, если необходимо
        data[elements_count++] = value; // Добавляем элемент и увеличиваем счётчик
    }

    // Метод удаления последнего элемента
    void pop_back() {
        if (empty()) { // Проверяем, что контейнер не пуст
            throw std::out_of_range("Cannot pop_back from an empty container");
        }
        --elements_count; // Уменьшаем счётчик элементов
    }

    // Метод вставки элемента в произвольную позицию
    void insert(size_t index, const T& value) {
        if (index > elements_count) { // Проверяем корректность индекса
            throw std::out_of_range("Insert index out of range");
        }
        resize_if_needed(); // Увеличиваем ёмкость, если необходимо
        std::copy_backward(data + index, data + elements_count, data + elements_count + 1); // Сдвигаем элементы вправо
        data[index] = value; // Вставляем новый элемент
        ++elements_count; // Увеличиваем счётчик элементов
    }

    // Метод удаления элемента по индексу
    void erase(size_t index) {
        if (index >= elements_count) { // Проверяем корректность индекса
            throw std::out_of_range("Erase index out of range");
        }
        std::copy(data + index + 1, data + elements_count, data + index); // Сдвигаем элементы влево
        --elements_count; // Уменьшаем счётчик элементов
    }

    // Метод доступа к элементу с проверкой индекса
    T& at(size_t index) {
        if (index >= elements_count) { // Проверяем корректность индекса
            throw std::out_of_range("Index " + std::to_string(index) + " is out of bounds");
        }
        return data[index]; // Возвращаем ссылку на элемент
    }

    // Константная версия метода at
    const T& at(size_t index) const {
        if (index >= elements_count) { // Проверяем корректность индекса
            throw std::out_of_range("Index " + std::to_string(index) + " is out of bounds");
        }
        return data[index]; // Возвращаем константную ссылку на элемент
    }

    // Метод проверки, является ли контейнер пустым
    bool empty() const {
        return elements_count == 0; // Возвращаем true, если элементов нет
    }

    // Метод получения текущего количества элементов
    size_t size() const {
        return elements_count; // Возвращаем количество элементов
    }

    // Метод очистки контейнера
    void clear() {
        delete[] data; // Освобождаем память
        data = nullptr; // Обнуляем указатель
        elements_count = 0; // Сбрасываем количество элементов
        // current_capacity остается прежним (как в std::vector)
    }

    // Метод резервирования памяти
    void reserve(size_t new_capacity) {
        if (new_capacity > current_capacity) { // Если новая ёмкость больше текущей
            T* new_data = new T[new_capacity]; // Создаем новый массив
            std::copy(data, data + elements_count, new_data); // Копируем элементы
            delete[] data; // Освобождаем старую память
            data = new_data; // Обновляем указатель
            current_capacity = new_capacity; // Обновляем ёмкость
        }
    }

    // Метод получения текущей ёмкости контейнера
    size_t get_capacity() const {
        return current_capacity; // Возвращаем текущую ёмкость
    }
};