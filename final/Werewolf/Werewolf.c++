#include "header.h"
#include "Werewolf.h"
#include "Base.h"

Werewolf::Werewolf(string name, int potion, int health, int strength, int shield){
    this->name = name;
    this->potion = potion;
    this->health = health;
    this->strength = strength;
    this->shield = shield;
    cout << "Werewolf with name: " << this->name << " just appeared."<< endl;
}

Werewolf::~Werewolf(){
    cout << "Werewolf with name: " << this->name << " died."<< endl;
}