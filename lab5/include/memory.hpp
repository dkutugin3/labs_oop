#ifndef REUSABLE_MEMORY_RESOURCE_HPP
#define REUSABLE_MEMORY_RESOURCE_HPP

#include <memory_resource>
#include <map>
#include <cstddef>
#include <stdexcept>

class ReusableMemoryResource : public std::pmr::memory_resource {
private:
    std::map<void*, std::size_t> allocated_blocks; // Хранит выделенные блоки памяти
    std::multimap<std::size_t, void*> free_blocks; // Хранит освобожденные блоки по размеру

protected:
    // Выделение памяти
    void* do_allocate(std::size_t bytes, std::size_t alignment) override;

    // Освобождение памяти
    void do_deallocate(void* p, std::size_t bytes, std::size_t alignment) override;

    // Проверка равенства ресурсов
    bool do_is_equal(const memory_resource& other) const noexcept override;

public:
    ~ReusableMemoryResource();
};

#endif // REUSABLE_MEMORY_RESOURCE_HPP
