#ifndef figure_h
#define figure_h

#include <string>

class Figure {
   public:
    struct Dot {
        double x, y;
    };

    Dot center() const;
    operator double() const;
    friend std::ostream& operator<<(std::ostream& stream, const Figure& fig);
    friend std::istream& operator>>(std::istream& stream, Figure& fig);

    Figure& operator=(const Figure& other);
    Figure& operator=(Figure&& other) noexcept;

    bool operator==(const Figure& other) const;
    bool operator!=(const Figure& other) const;

    Figure() : n(0) {}
    ~Figure() { delete[] peak; }

   protected:
    std::ostream& write(std::ostream& stream) const;
    std::istream& read(std::istream& stream);
    double distance(const Figure::Dot& a, const Figure::Dot& b);
    int n;
    Dot* peak;
};

#endif