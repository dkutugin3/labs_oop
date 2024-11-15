#ifndef money_h
#define money_h

// #include <iostream>
#include <string>

class Money {
   private:
    size_t size;
    unsigned char* array;

   public:
    Money();
    Money(const size_t& n, unsigned char t);
    Money(const std::initializer_list<unsigned char>& t);
    Money(const std::string& t);
    Money(const Money& other);
    Money(Money&& other) noexcept;

    bool operator==(const Money& other) const;
    bool operator!=(const Money& other) const;
    bool operator<(const Money& other) const;
    bool operator>(const Money& other) const;

    Money& operator=(const Money& other);
    Money& operator+=(const Money& other);
    Money& operator-=(const Money& other);

    std::ostream& print(std::ostream& os) const;

    virtual ~Money() noexcept;
};

#endif