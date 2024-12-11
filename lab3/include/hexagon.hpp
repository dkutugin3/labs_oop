#ifndef Hexagon_h
#define Hexagon_h

#include <iostream>
#include "figure.hpp"
class Hexagon : public Figure {
   public:
    Hexagon() {
        n = 6;
        peak = new Dot[n];
    }
};

#endif