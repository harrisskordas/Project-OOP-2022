#ifndef Werewolf_h  //header guard
#define Werewolf_h  //so it protexts itself not to copy the same header file twice

#include "header.h"
#include "Base.h"

class Werewolf : public Base{
    public:
        Werewolf(string ,int ,int, int, int);
        ~Werewolf();
};

#endif