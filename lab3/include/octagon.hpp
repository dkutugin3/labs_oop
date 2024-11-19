#ifndef Octagon_h
#define Octagon_h

#include "figure.hpp"
#include <iostream>
class Octagon : public Figure {
public:
    Octagon(){
        n = 8;
        peak = new Dot[n];
    }
};
#endif