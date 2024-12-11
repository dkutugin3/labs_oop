template <typename T>
void DynamicArray<T>::grow() {
    std::size_t new_capacity = capacity ? capacity * 2 : 1;
    T* new_data = allocator.allocate(new_capacity);

    for (std::size_t i = 0; i < size; ++i) {
        allocator.construct(&new_data[i], std::move(data[i]));
        allocator.destroy(&data[i]);
    }
    if (capacity) {
        allocator.deallocate(data, capacity);
    }
    data = new_data;
    capacity = new_capacity;
}

template <typename T>
DynamicArray<T>::DynamicArray(std::pmr::memory_resource* resource)
    : allocator(resource), data(nullptr), size(0), capacity(0) {}

template <typename T>
DynamicArray<T>::~DynamicArray() {
    for (std::size_t i = 0; i < size; ++i) {
        allocator.destroy(&data[i]);
    }
    allocator.deallocate(data, capacity);
}

template <typename T>
void DynamicArray<T>::push_back(const T& value) {
    if (size == capacity) {
        grow();
    }
    allocator.construct(&data[size], value);
    ++size;
}

template <typename T>
void DynamicArray<T>::push_back(T&& value) {
    if (size == capacity) {
        grow();
    }
    allocator.construct(&data[size], std::move(value));
    ++size;
}

template <typename T>
T& DynamicArray<T>::operator[](std::size_t index) {
    if (index >= size)
        throw std::out_of_range("Index out of range");
    return data[index];
}

template <typename T>
const T& DynamicArray<T>::operator[](std::size_t index) const {
    if (index >= size)
        throw std::out_of_range("Index out of range");
    return data[index];
}

template <typename T>
std::size_t DynamicArray<T>::get_size() const {
    return size;
}

// Итератор

template <typename T>
DynamicArray<T>::Iterator::Iterator(T* p) : ptr(p) {}

template <typename T>
typename DynamicArray<T>::Iterator::reference
DynamicArray<T>::Iterator::operator*() const {
    return *ptr;
}

template <typename T>
typename DynamicArray<T>::Iterator::pointer
DynamicArray<T>::Iterator::operator->() const {
    return ptr;
}

template <typename T>
typename DynamicArray<T>::Iterator& DynamicArray<T>::Iterator::operator++() {
    ++ptr;
    return *this;
}

template <typename T>
typename DynamicArray<T>::Iterator DynamicArray<T>::Iterator::operator++(int) {
    Iterator tmp = *this;
    ++(*this);
    return tmp;
}

template <typename T>
bool DynamicArray<T>::Iterator::operator==(const Iterator& other) const {
    return ptr == other.ptr;
}

template <typename T>
bool DynamicArray<T>::Iterator::operator!=(const Iterator& other) const {
    return ptr != other.ptr;
}

template <typename T>
typename DynamicArray<T>::Iterator DynamicArray<T>::begin() {
    return Iterator(data);
}

template <typename T>
typename DynamicArray<T>::Iterator DynamicArray<T>::end() {
    return Iterator(data + size);
}
