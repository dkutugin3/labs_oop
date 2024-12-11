#ifndef Childs_h
#define Childs_h
#include "./figure.hpp" 
template <Scalar T>
class Pentagon : public Figure<T> {
    std::unique_ptr<Point<T>[]> vertices;
    T radius; // Радиус вписанной окружности
    Point<T> center_point;

public:
    Pentagon(Point<T> center, T r) 
        : radius(r), center_point(center), vertices(std::make_unique<Point<T>[]>(5)) {
        // Вычисляем вершины
        for (int i = 0; i < 5; ++i) {
            T angle = 2 * M_PI * i / 5; // Угол для вершины
            vertices[i].x = center.x + radius * std::cos(angle);
            vertices[i].y = center.y + radius * std::sin(angle);
        }
    }

    T area() const override {
        return 5 * (radius * radius * std::sin(2 * M_PI / 5)) / 2;
    }

    Point<T> center() const override {
        return center_point;
    }

    void print(std::ostream& os) const override {
        os << "Pentagon: Center " << center_point << ", Radius " << radius << "\nVertices:";
        for (int i = 0; i < 5; ++i) {
            os << " " << vertices[i];
        }
        os << ", Area " << area();
    }
};

template <Scalar T>
class Hexagon : public Figure<T> {
    std::unique_ptr<Point<T>[]> vertices;
    T radius; // Радиус вписанной окружности
    Point<T> center_point;

public:
    Hexagon(Point<T> center, T r) 
        : radius(r), center_point(center), vertices(std::make_unique<Point<T>[]>(6)) {
        // Вычисляем вершины
        for (int i = 0; i < 6; ++i) {
            T angle = 2 * M_PI * i / 6; // Угол для вершины
            vertices[i].x = center.x + radius * std::cos(angle);
            vertices[i].y = center.y + radius * std::sin(angle);
        }
    }

    T area() const override {
        return 3 * std::sqrt(3) * radius * radius / 2;
    }

    Point<T> center() const override {
        return center_point;
    }

    void print(std::ostream& os) const override {
        os << "Hexagon: Center " << center_point << ", Radius " << radius << "\nVertices:";
        for (int i = 0; i < 6; ++i) {
            os << " " << vertices[i];
        }
        os << ", Area " << area();
    }
};


template <Scalar T>
class Octagon : public Figure<T> {
    std::unique_ptr<Point<T>[]> vertices;
    T radius; // Радиус вписанной окружности
    Point<T> center_point;

public:
    Octagon(Point<T> center, T r) 
        : radius(r), center_point(center), vertices(std::make_unique<Point<T>[]>(8)) {
        // Вычисляем вершины
        for (int i = 0; i < 8; ++i) {
            T angle = 2 * M_PI * i / 8; // Угол для вершины
            vertices[i].x = center.x + radius * std::cos(angle);
            vertices[i].y = center.y + radius * std::sin(angle);
        }
    }

    T area() const override {
        return 2 * (1 + std::sqrt(2)) * radius * radius;
    }

    Point<T> center() const override {
        return center_point;
    }

    void print(std::ostream& os) const override {
        os << "Octagon: Center " << center_point << ", Radius " << radius << "\nVertices:";
        for (int i = 0; i < 8; ++i) {
            os << " " << vertices[i];
        }
        os << ", Area " << area();
    }
};

#endif