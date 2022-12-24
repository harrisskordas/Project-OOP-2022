#ifndef Avatar_h  //header guard
#define Avatar_h  //so it protexts itself not to copy the same header file twice

#include "header.h"
#include "Base.h"

class Avatar : public Base{
    public:
        Avatar(string ,int );
        ~Avatar();
        void addpotion();
};

#endif