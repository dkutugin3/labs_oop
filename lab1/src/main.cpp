#include <iostream>
#include "function.cpp"
int main() {
    std::cout << "Введите строку" << std::endl;
    std::string str;
    std::getline(std::cin, str, '\n');
    std::cout << removeVowels(str) << std::endl;
    return 0;
}