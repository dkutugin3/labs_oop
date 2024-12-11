#include <iostream>
#include <string>
#include "../include/memory.hpp"
#include "../include/array.hpp"

int main() {
    ReusableMemoryResource memory_resource;
   
    DynamicArray<int> dynamic_array(&memory_resource);

    while (true) {
        std::cout << "\n=== Меню ===\n";
        std::cout << "1. Добавить элемент\n";
        std::cout << "2. Показать элементы массива\n";
        std::cout << "3. Выйти\n";
        std::cout << "Введите номер действия: ";

        int choice;
        std::cin >> choice;

        if (choice == 1) {
            std::cout << "Введите значение для добавления: ";
            int value;
            std::cin >> value;
            dynamic_array.push_back(value);
            std::cout << "Элемент добавлен!\n";
        } else if (choice == 2) {
            if (dynamic_array.get_size() == 0) {
                std::cout << "Массив пуст.\n";
            } else {
                std::cout << "Элементы массива: ";
                for (auto it = dynamic_array.begin(); it != dynamic_array.end(); ++it) {
                    std::cout << *it << " ";
                }
                std::cout << "\n";
            }
        } else if (choice == 3) {
            std::cout << "Выход из программы.\n";
            break;
        } else {
            std::cout << "Неверный ввод. Попробуйте снова.\n";
        }
    }

    return 0;
}
