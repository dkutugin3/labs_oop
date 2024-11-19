#ifndef Pentagon_h
#define Pentagon_h

#include "figure.hpp"
#include <iostream>
class Pentagon : public Figure {
public:
    Pentagon(){
        n = 5;
        peak = new Dot[n];
    }    
};
#endif