#ifndef Vampire_h  //header guard
#define Vampire_h  //so it protexts itself not to copy the same header file twice

#include "header.h"
#include "Base.h"

class Vampire : public Base{
    public:
        Vampire(string ,int ,int, int, int);
        ~Vampire();
};

#endif