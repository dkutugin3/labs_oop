#ifndef Hexagon_h
#define Hexagon_h

#include "figure.hpp"
#include <iostream>
class Hexagon : public Figure {
public:
    Hexagon(){
        n = 6;
        peak = new Dot[n];
    }
};

#endif