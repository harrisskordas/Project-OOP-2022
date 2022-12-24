#include "header.h"
#include "Vampire.h"
#include "Base.h"

Vampire::Vampire(string name, int potion, int health, int strength, int shield){
    this->name = name;
    this->potion = potion;
    this->health = health;
    this->strength = strength;
    this->shield = shield;
    cout << "Vampire with name: " << this->name << " just appeared."<< endl;
}

Vampire::~Vampire(){
    cout << "Vampire with name: " << this->name << " died."<< endl;
}