#pragma once

#include <stdexcept>
#include <string>
#include <algorithm>
#include <initializer_list>

template <typename T>
class SequentialContainer {
private:
    T* data = nullptr;
    size_t elements_count = 0;
    size_t current_capacity = 0;

    void resize_if_needed() {
        if (elements_count == current_capacity) {
            size_t new_capacity = current_capacity == 0 ? 1 : current_capacity * 2;
            T* new_data = new T[new_capacity];
            try {
                std::copy(data, data + elements_count, new_data);
            } catch (...) {
                delete[] new_data;
                throw;
            }
            delete[] data;
            data = new_data;
            current_capacity = new_capacity;
        }
    }

public:
    SequentialContainer() = default;

    SequentialContainer(const SequentialContainer& other)
        : elements_count(other.elements_count), current_capacity(other.current_capacity) {
        if (current_capacity > 0) {
            data = new T[current_capacity];
            try {
                std::copy(other.data, other.data + elements_count, data);
            } catch (...) {
                delete[] data;
                throw;
            }
        }
    }

    SequentialContainer& operator=(const SequentialContainer& other) {
        if (this != &other) {
            SequentialContainer temp(other);
            std::swap(data, temp.data);
            std::swap(elements_count, temp.elements_count);
            std::swap(current_capacity, temp.current_capacity);
        }
        return *this;
    }

    SequentialContainer(SequentialContainer&& other) noexcept
        : data(other.data), elements_count(other.elements_count), current_capacity(other.current_capacity) {
        other.data = nullptr;
        other.elements_count = other.current_capacity = 0;
    }

    SequentialContainer& operator=(SequentialContainer&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            elements_count = other.elements_count;
            current_capacity = other.current_capacity;
            other.data = nullptr;
            other.elements_count = other.current_capacity = 0;
        }
        return *this;
    }

    ~SequentialContainer() {
        delete[] data;
    }

    void push_back(const T& value) {
        resize_if_needed();
        data[elements_count++] = value;
    }

    void pop_back() {
        if (empty()) {
            throw std::out_of_range("Cannot pop_back from an empty container");
        }
        --elements_count;
    }

    void insert(size_t index, const T& value) {
        if (index > elements_count) {
            throw std::out_of_range("Insert index out of range");
        }
        resize_if_needed();
        std::copy_backward(data + index, data + elements_count, data + elements_count + 1);
        data[index] = value;
        ++elements_count;
    }

    void erase(size_t index) {
        if (index >= elements_count) {
            throw std::out_of_range("Erase index out of range");
        }
        std::copy(data + index + 1, data + elements_count, data + index);
        --elements_count;
    }

    T& at(size_t index) {
        if (index >= elements_count) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[index];
    }

    const T& at(size_t index) const {
        if (index >= elements_count) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[index];
    }

    bool empty() const {
        return elements_count == 0;
    }

    size_t size() const {
        return elements_count;
    }

    void clear() {
        delete[] data;
        data = nullptr;
        elements_count = 0;
    }

    void reserve(size_t new_capacity) {
        if (new_capacity > current_capacity) {
            T* new_data = new T[new_capacity];
            try {
                std::copy(data, data + elements_count, new_data);
            } catch (...) {
                delete[] new_data;
                throw;
            }
            delete[] data;
            data = new_data;
            current_capacity = new_capacity;
        }
    }

    size_t get_capacity() const {
        return current_capacity;
    }

    void shrink_to_fit() {
        if (elements_count < current_capacity) {
            T* new_data = new T[elements_count];
            try {
                std::copy(data, data + elements_count, new_data);
            } catch (...) {
                delete[] new_data;
                throw;
            }
            delete[] data;
            data = new_data;
            current_capacity = elements_count;
        }
    }
};