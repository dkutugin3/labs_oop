#ifndef Pentagon_h
#define Pentagon_h

#include <iostream>
#include "figure.hpp"
class Pentagon : public Figure {
   public:
    Pentagon() {
        n = 5;
        peak = new Dot[n];
    }
};
#endif