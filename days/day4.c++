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

class Base{
    protected:
        string name;
        int potion;
        int health;
    public:
        string getname();
        void attack(Base& , int );      //alternative   void attack(Base* , int ); 
        int getpotion();
        void setpotion(int );
        void sethealth(int );
        int gethealth();
};

void Base::attack(Base& crea, int damage){    //alternative void attack(Base* , int ); crea->
    crea.sethealth(damage);
}

string Base::getname(){
    return this->name;
}

int Base::getpotion(){
    return this->potion;
}

void Base::setpotion(int num){
    this->potion = this->potion - num;
}

void Base::sethealth(int damage){
    this->health = this->health - damage;
}

int Base::gethealth(){
    return this->health;
}

class Vampire : public Base{
    public:
        Vampire(string ,int ,int);
        ~Vampire();
};

Vampire::Vampire(string name, int potion, int health){
    this->name = name;
    this->potion = potion;
    this->health = health;
    cout << "Vampire with name: " << this->name << " just appeared."<< endl;
}

Vampire::~Vampire(){
    cout << "Vampire with name: " << this->name << " died."<< endl;
}

class Werewolf : public Base{
    public:
        Werewolf(string ,int ,int);
        ~Werewolf();
};

Werewolf::Werewolf(string name, int potion, int health){
    this->name = name;
    this->potion = potion;
    this->health = health;
    cout << "Werewolf with name: " << this->name << " just appeared."<< endl;
}

Werewolf::~Werewolf(){
    cout << "Werewolf with name: " << this->name << " died."<< endl;
}

class Terrain : public Base{
    public:
        Terrain(string );
};

Terrain::Terrain(string ter){
	this->name = ter;
}

class MapTile{
	private:
		Base* map[5];
	public:
		MapTile();
		void setinfo(Base* , int , int );
		void display();
		
};

MapTile::MapTile(){
	cout << "Map created" << endl;
}

void MapTile::setinfo(Base* cr, int i, int j){
	this->map[i] = cr;
}

void MapTile::display(){
    cout << "Display of the map:" << endl;
	for (int i=0; i<5; i++){
        for (int j = 0; j < 5; j++)
        {
            cout << this->map[i]->getname() << " ";
        }
        cout << endl;
	}
}


int main(void){

    MapTile map;
	vector<Vampire*> vv;
    vector<Werewolf*> vw;
    int wx,wy;
    int x=5;    //einai oi diastases
    srand((unsigned)time(NULL));

    for(int i=0; i<5; i++){
        wx=rand()%(x);      //έλεγξε οτι δεν έχει μπει πριν κάποιο
        wy=rand()%(x);
        string strv = "V";
        strv = strv + to_string(i);
        Vampire* v = new Vampire(strv, 2, 2);
        map.setinfo(v, wx, wy);
        vv.push_back(v);
    }

    map.display();

    //dynamic to do
	//Terrain w("W");
	//map.setinfo(w, 0, 0);
    //map.display();

	//map.setinfo(v4, 0, 0);
	//map.setinfo(v, 1, 1);
	//map.display();

    for (int i = 0; i < vv.size(); ++i) {
        delete vv[i]; // Calls ~object and deallocates *tmp[i]
    }

    vv.clear(); //clears the vector
	return 0;
}