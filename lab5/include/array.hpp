#ifndef DYNAMIC_ARRAY_HPP
#define DYNAMIC_ARRAY_HPP

#include <memory_resource>
#include <stdexcept>
#include <iterator>

template <typename T>
class DynamicArray {
private:
    using Allocator = std::pmr::polymorphic_allocator<T>;
    Allocator allocator;
    T* data;
    std::size_t size;
    std::size_t capacity;

    void grow();

public:
    explicit DynamicArray(std::pmr::memory_resource* resource = std::pmr::get_default_resource());
    ~DynamicArray();

    void push_back(const T& value);
    void push_back(T&& value);

    T& operator[](std::size_t index);
    const T& operator[](std::size_t index) const;

    std::size_t get_size() const;

    // Итератор
    class Iterator {
        T* ptr;

    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using pointer = T*;
        using reference = T&;

        explicit Iterator(T* p);

        reference operator*() const;
        pointer operator->() const;

        Iterator& operator++();
        Iterator operator++(int);

        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;
    };

    Iterator begin();
    Iterator end();
};

#include "../src/array.tpp"

#endif 
