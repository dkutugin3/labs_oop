#ifndef Octagon_h
#define Octagon_h

#include <iostream>
#include "figure.hpp"
class Octagon : public Figure {
   public:
    Octagon() {
        n = 8;
        peak = new Dot[n];
    }
};
#endif