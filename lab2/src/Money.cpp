#include "../include/Money.hpp"
#include <algorithm>
#include <cstring>
#include <iostream>
#include <stdexcept>

Money::Money() : size(1), array(new unsigned char[1]{}) {}

Money::Money(const size_t& n, unsigned char t)
    : size(n), array(new unsigned char[n]) {
    if (!isdigit(t)) {
        throw std::invalid_argument("Неверное значение");
    }
    std::fill(array, array + n, t - '0');
}

Money::Money(const std::initializer_list<unsigned char>& t)
    : size(t.size()), array(new unsigned char[size]) {
    for (unsigned char i : t) {
        if (!isdigit(i)) {
            throw std::invalid_argument("Неверное значение");
        }
    }
    for (size_t i = 0; i < size; ++i) {
        array[i] = t.begin()[size - 1 - i] - '0';
    }
}

Money::Money(const std::string& t)
    : size(t.size()), array(new unsigned char[size]) {
    for (size_t i = 0; i < size; ++i) {
        if (!isdigit(t[i])) {
            throw std::invalid_argument("Строка должна содержать только цифры");
        }
        array[size - 1 - i] = t[i] - '0';
    }
}

std::ostream& Money::print(std::ostream& os) const {
    for (int i = size - 1; i >= 0; --i) {
        if (i == 1 && size > 2) {
            os << ".";
        }
        os << static_cast<char>(array[i] + '0');
    }
    os << std::endl;
    return os;
}


Money::Money(const Money& other)
    : size(other.size), array(new unsigned char[size]) {
    std::copy(other.array, other.array + size, array);
}


Money::Money(Money&& other) noexcept : size(other.size), array(other.array) {
    other.size = 1;
    other.array = new unsigned char[1]{};
}


bool Money::operator==(const Money& other) const {
    if (size != other.size) {
        return false;
    }
    for (size_t i = 0; i < size; ++i) {
        if (array[i] != other.array[i]) {
            return false;
        }
    }
    return true;
}

bool Money::operator!=(const Money& other) const {
    return !(*this == other);
}


bool Money::operator<(const Money& other) const {
    if (size != other.size) {
        return size < other.size;
    }
    for (int i = size - 1; i >= 0; i--) {
        if (array[i] != other.array[i]) {
            return array[i] < other.array[i];
        }
    }
    return false;
}


bool Money::operator>(const Money& other) const {
    if (*this != other) {
        return !(*this < other);
    }
    return false;
}


Money& Money::operator=(const Money& other) {
    if (this == &other) {
        return *this;
    }
    delete[] array;
    size = other.size;
    array = new unsigned char[size];
    for (size_t i = 0; i < size; ++i) {
        array[i] = other.array[i];
    }
    return *this;
}


Money& Money::operator+=(const Money& other) {
    int maxSize = std::max(size, other.size);
    unsigned char* result = new unsigned char[maxSize + 1];
    int resultSize = maxSize;
    unsigned char carry = 0;
    for (int i = 0; i < maxSize; ++i) {
        unsigned char digitThis = (i < size) ? array[i] : 0;
        unsigned char digitOther = (i < other.size) ? other.array[i] : 0;
        unsigned char sum = digitThis + digitOther + carry;
        if (sum >= 10) {
            sum -= 10;
            carry = 1;
        } else {
            carry = 0;
        }
        result[i] = sum;
    }
    if (carry > 0) {
        result[resultSize] = carry;
        ++resultSize;
    }
    delete[] array;
    array = result;
    size = resultSize;
    return *this;
}


Money& Money::operator-=(const Money& other) {
    if (other.size > size) {
        throw std::invalid_argument("Вычитаемое число слишком большое");
    }
    unsigned char borrow = 0;
    for (int i = 0; i < size; ++i) {
        unsigned char digitThis = array[i];
        unsigned char digitOther = (i < other.size) ? other.array[i] : 0;

        int diff = digitThis - digitOther - borrow;

        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        array[i] = static_cast<unsigned char>(diff);
    }
    while (size > 1 && array[size - 1] == 0) {
        --size;
    }
    return *this;
}

Money::~Money() {
    delete[] array;
}