#include "../include/figure.hpp"
#include <cmath>
#include <iostream>
#include <stdexcept>
std::ostream& operator<<(std::ostream& stream, const Figure& fig) {
    return fig.write(stream);
}

std::istream& operator>>(std::istream& stream, Figure& fig) {
    return fig.read(stream);
}

double Figure::distance(const Figure::Dot& a, const Figure::Dot& b) {
    return std::sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
};

Figure::operator double() const {
    double area = 0.0;
    for (int i = 0; i < n; ++i) {
        const Dot& current = this->peak[i];
        const Dot& next = this->peak[(i + 1) % 5];
        area += current.x * next.y - current.y * next.x;
    }
    return std::abs(area) / 2.0;
}

Figure::Dot Figure::center() const {
    Dot center;
    center.x = 0.0;
    center.y = 0.0;
    for (int i = 0; i < n; ++i) {
        Dot& dot = peak[i];
        center.x += dot.x;
        center.y += dot.y;
    }
    center.x /= n;
    center.y /= n;
    return center;
}

Figure& Figure::operator=(const Figure& other) {
    if (n != other.n) {
        std::cerr << "Warning: Figures have different sizes!" << std::endl;
        return *this;
    }
    if (this != &other) {
        for (int i = 0; i < n; ++i) {
            peak[i] = other.peak[i];
        }
    }
    return *this;
}

Figure& Figure::operator=(Figure&& other) noexcept {
    if (n != other.n) {
        std::cerr << "Warning: Figures have different sizes!" << std::endl;
        return *this;
    }
    if (this != &other) {
        delete[] peak;
        peak = other.peak;
        other.peak = nullptr;
    }
    return *this;
};

bool Figure::operator==(const Figure& other) const {
    if (n != other.n) {
        return false;
    }
    for (int i = 0; i < n; ++i) {
        if ((peak[i].x != other.peak[i].x) || (peak[i].y != other.peak[i].y)) {
            return false;
        }
    }
    return true;
}

bool Figure::operator!=(const Figure& other) const {
    return !(*this == other);
}

std::ostream& Figure::write(std::ostream& stream) const {
    for (int i = 0; i < n; ++i) {
        Dot& dot = peak[i];
        stream << " (" << dot.x << "," << dot.y << ")";
    }
    stream << "\n";
    return stream;
}

std::istream& Figure::read(std::istream& stream) {
    for (int i = 0; i < n; ++i) {
        Dot& dot = peak[i];
        stream >> dot.x >> dot.y;
    }
    return stream;
}