#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <iterator>
#include <experimental/iterator>
#include <chrono>
#include <thread>
#include <time.h>
using namespace std;

int const x = 3;
int const y = 3;

class Creature{
    protected:
        string name;
        int potion;
        int health;
    public:
        string getname();
        void attack(Creature& , int );      //alternative   void attack(Creature* , int ); 
        int getpotion();
        void setpotion(int );
        void sethealth(int );
        int gethealth();
};

void Creature::attack(Creature& crea, int damage){    //alternative void attack(Creature* , int ); crea->
    crea.sethealth(damage);
}

string Creature::getname(){
    return this->name;
}

int Creature::getpotion(){
    return this->potion;
}

void Creature::setpotion(int num){
    this->potion = this->potion - num;
}

void Creature::sethealth(int damage){
    this->health = this->health - damage;
}

int Creature::gethealth(){
    return this->health;
}

class Vampire : public Creature{
    public:
        Vampire(string ,int ,int);
        ~Vampire();
};

Vampire::Vampire(string name, int potion, int health){
    this->name = name;
    this->potion = potion;
    this->health = health;
}

Vampire::~Vampire(){
}

class Werewolf : public Creature{
    public:
        Werewolf(string ,int ,int);
        ~Werewolf();
};

Werewolf::Werewolf(string name, int potion, int health){
    this->name = name;
    this->potion = potion;
    this->health = health;
}

Werewolf::~Werewolf(){
}

bool check_terrain(string terrain[x][y], int a, int b){
    if ((terrain[a][b]) == "EA"){
        return true;
    }else{
        return false;
    }
}

int main(void){

    vector<Vampire> vv;
    vector<Werewolf> vw;

    int num = x;

    for(int i=0; i<num; i++){
        string strv = "V";
        strv = strv + to_string(i);
        Vampire v(strv, 2, 2);
        vv.push_back(v);
    }

    for(int i=0; i<num; i++){
        string strw = "W";
        strw = strw + to_string(i);
        Werewolf w(strw, 2, 2);
        vw.push_back(w);
    }

    for(int i=0; i<vv.size(); i++){
        cout << vv[i].getname() << " has " << vv[i].getpotion() << " and " << vv[i].gethealth() << endl;
    }

    for(int i=0; i<vw.size(); i++){
        cout << vw[i].getname() << " has " << vw[i].getpotion() << " and " << vw[i].gethealth() << endl;
    }

    

    //vv[0].setpotion(1);
    //vv[2].setpotion(2);
    //vv[0].sethealth(50);
    //vv[2].sethealth(20);

    //cout << vv[0].getname() << " has " << vv[0].getpotion() << endl;
    //cout << vv[2].getname() << " has " << vv[2].getpotion() << endl;
    //cout << vv[0].getname() << " has " << vv[0].gethealth() << endl;
    //cout << vv[2].getname() << " has " << vv[2].gethealth() << endl;

    vw[0].attack(vv[1], 20);    //alternative vw[0].attack(&vv[1], 20);
    cout << vw[0].getname() << " is attacking to " << vv[1].getname() << endl;
    cout << "After hit, " << vv[1].getname() << " has health: " << vv[1].gethealth() << endl;

    vv[2].attack(vw[0], 20);    //alternative vw[0].attack(&vv[1], 20);
    cout << vv[2].getname() << " is attacking to " << vw[0].getname() << endl;
    cout << "After hit, " << vw[0].getname() << " has health: " << vw[0].gethealth() << endl;
    
    Creature terrain[5][5];

    vv.clear(); //not necessary,vector destroys itself automatically
    return 0;
}



//cout << map[i][j].getname() << " ";
//cout << this->map[i][j].getname() << " ";
//cout << this->map[i]->getname() << " ";
