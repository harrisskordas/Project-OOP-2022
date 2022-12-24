#ifndef Base_h  //header guard
#define Base_h  //so it protexts itself not to copy the same header file twice

#include "header.h"

class Base{
    protected:
        string name;
        int potion;
        int health;
        int strength;
        int shield;
    public:
        Base();
        ~Base();
        string getname() const;
        void attack(Base* , int );      //alternative   void attack(Base* , int );
        void heal(Base* , int ); 
        int getpotion() const;
        void subpotion();
        void sethealth(int );
        int gethealth() const;
        int getshield() const;
        int getstrength() const;
};

#endif