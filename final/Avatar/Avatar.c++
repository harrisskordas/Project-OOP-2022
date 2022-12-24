#include "Avatar.h"

Avatar::Avatar(string name, int potion){
    this->name = name;
    this->potion = 1;
    cout << "Your Avatar with sign: " << this->name << " just created."<< endl;
    cout << "You have: " << this->potion << " potion."<< endl;
}

Avatar::~Avatar(){
    cout << "Your avatar is destroyed!"<< endl;
}

void Avatar::addpotion(){
    this->potion = this->potion + 1;
}