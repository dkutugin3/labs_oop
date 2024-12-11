#ifndef Figure_h
#define Figure_h

#include <iostream>
#include <memory>
#include <vector>
#include <cmath>
#include <type_traits>

template <typename T>
concept Scalar = std::is_scalar_v<T>;

template <Scalar T>
struct Point {
    T x, y;
    Point(T x = 0, T y = 0) : x(x), y(y) {}
    friend std::ostream& operator<<(std::ostream& os, const Point& p) {
        return os << "(" << p.x << ", " << p.y << ")";
    }
};



template <Scalar T>
class Figure {
public:
    virtual ~Figure() = default;

    virtual T area() const = 0;
    virtual Point<T> center() const = 0;
    virtual void print(std::ostream& os) const = 0;


    operator double() const {
        return static_cast<double>(area());
    }

    friend std::ostream& operator<<(std::ostream& os, const Figure<T>& fig) {
        fig.print(os);
        return os;
    }
};

#endif