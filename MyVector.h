#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

template <typename T>
class MyVector
{
private:
    T *data;
    size_t capacity;
    size_t size;

    void resize(size_t new_capacity)
    {
        T *new_data = new T[new_capacity](); // khoi tao mac dinh
        for (size_t i = 0; i < size; i++)
        {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }

public:
    // Constructor
    MyVector() : data(nullptr), capacity(0), size(0) {}

    MyVector(size_t initial_capacity) : capacity(initial_capacity), size(0)
    {
        data = new T[capacity](); // khởi tạo mặc định
    }

    // Destructor
    ~MyVector()
    {
        delete[] data;
    }

    // Copy constructor
    MyVector(const MyVector &other) : capacity(other.capacity), size(other.size)
    {
        data = new T[capacity](); // khoi tao mac dinh
        for (size_t i = 0; i < size; i++)
        {
            data[i] = other.data[i];
        }
    }

    // Copy assignment operator
    MyVector &operator=(const MyVector &other)
    {
        if (this != &other)
        {
            delete[] data;
            capacity = other.capacity;
            size = other.size;
            data = new T[capacity](); // khoi tao mac dinh
            for (size_t i = 0; i < size; i++)
            {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    // Them elenment vao cuoi
    void push_back(const T &value)
    {
        if (size >= capacity)
        {
            size_t new_capacity = (capacity == 0) ? 1 : capacity * 2;
            resize(new_capacity);
        }
        data[size++] = value;
    }

    // xoa element tai i
    void remove_at(size_t index)
    {
        if (index >= size)
        {
            throw out_of_range("Index out of range");
        }
        for (size_t i = index; i < size - 1; i++)
        {
            data[i] = data[i + 1];
        }
        size--;
    }

    // Truy cap element tai i
    T &operator[](size_t index)
    {
        if (index >= size)
        {
            throw out_of_range("Index out of range");
        }
        return data[index];
    }

    const T &operator[](size_t index) const
    {
        if (index >= size)
        {
            throw out_of_range("Index out of range");
        }
        return data[index];
    }

    // Get size
    size_t get_size() const
    {
        return size;
    }
    // Get capacity
    size_t get_capacity() const
    {
        return capacity;
    }
    // Check if empty
    bool empty() const
    {
        return size == 0;
    }
    // Clear vector
    void clear()
    {
        size = 0;
    }
    // Iterators
    T *begin()
    {
        return data;
    }
    T *end()
    {
        return data + size;
    }
    const T *begin() const
    {
        return data;
    }
    const T *end() const
    {
        return data + size;
    }
};

#endif