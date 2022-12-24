#include "Base.h"

Base::Base(){}

Base::~Base(){}

void Base::attack(Base* crea, int damage){    //alternative void attack(Base* , int ); crea->
    crea->sethealth(damage);
}

void Base::heal(Base* crea, int damage){    //alternative void attack(Base* , int ); crea->
    crea->sethealth(damage);
}

string Base::getname() const{
    return this->name;
}

int Base::getpotion() const{
    return this->potion;
}

void Base::subpotion(){
    this->potion = this->potion - 1;
}

void Base::sethealth(int damage){   //for heal we have damage = -1...so it becomes   this->health = this->health - (-damage);
    this->health = this->health - damage;
}

int Base::gethealth() const{
    return this->health;
}

int Base::getshield() const{
    return this->shield;
}

int Base::getstrength() const{
    return this->strength;
}