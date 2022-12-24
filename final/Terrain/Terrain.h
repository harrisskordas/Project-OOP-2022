#ifndef Terrain_h  //header guard
#define Terrain_h  //so it protexts itself not to copy the same header file twice

#include "header.h"
#include "Base.h"

class Terrain : public Base{
    public:
        Terrain(string );
        ~Terrain();
};

#endif