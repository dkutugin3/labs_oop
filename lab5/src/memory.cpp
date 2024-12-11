#include "../include/memory.hpp"
#include <new>
#include <iostream>

// Выделение памяти
void* ReusableMemoryResource::do_allocate(std::size_t bytes, std::size_t alignment) {
    // Проверяем, есть ли свободный блок нужного размера
    auto it = free_blocks.lower_bound(bytes);
    if (it != free_blocks.end()) {
        void* ptr = it->second;
        allocated_blocks[ptr] = it->first;
        free_blocks.erase(it); // Удаляем из свободных блоков
        return ptr;
    }

    // Если свободного блока нет, выделяем новый
    void* ptr = ::operator new(bytes, std::align_val_t(alignment));
    allocated_blocks[ptr] = bytes;
    return ptr;
}

// Освобождение памяти
void ReusableMemoryResource::do_deallocate(void* p, std::size_t bytes, std::size_t alignment) {
    auto it = allocated_blocks.find(p);
    if (it != allocated_blocks.end()) {
        std::size_t size = it->second;
        allocated_blocks.erase(it);
        free_blocks.emplace(size, p); // Добавляем в свободные блоки
    } else {
        throw std::runtime_error("Attempt to deallocate untracked memory!");
    }
}

// Проверка равенства ресурсов
bool ReusableMemoryResource::do_is_equal(const memory_resource& other) const noexcept {
    return this == &other;
}

// Деструктор
ReusableMemoryResource::~ReusableMemoryResource() {
    // Очищаем всю неосвобожденную память
    for (auto& [ptr, size] : allocated_blocks) {
        ::operator delete(ptr, std::align_val_t(alignof(std::max_align_t)));
    }
    allocated_blocks.clear();

    // Также очищаем освобожденную память
    for (auto& [size, ptr] : free_blocks) {
        ::operator delete(ptr, std::align_val_t(alignof(std::max_align_t)));
    }
    free_blocks.clear();
}
