#include <iostream>
using namespace std;

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

class Terrain : public Creature{
    public:
        Terrain(string );
};

Terrain::Terrain(string ter){
	this->name = ter;
}

class MapTile{
	private:
		Creature map[2][2];
	public:
		MapTile();
		void setinfo(Creature& , int , int );
		void seemap();
		
};

void MapTile::setinfo(Creature& cr, int i, int j){
	this->map[i][j] = cr;
}

void MapTile::seemap(){
	for (int i=0; i<2; i++){
		for(int j=0; j<2; j++){
			cout << this->map[i][j].getname() << " ";
		}
		cout << endl;
	}
}

MapTile::MapTile(){
	cout << "Map created" << endl;
}


int main(void){

	Vampire v("V1", 2, 2);
	Vampire v2("V2", 2, 2);
	Vampire v3("V3", 2, 2);
	Vampire v4("V4", 2, 2);

	cout << v.getname() << " has " << v.getpotion() << " and " << v.gethealth() << endl;

	MapTile map;
	map.setinfo(v, 0, 0);
	map.setinfo(v2, 0, 1);
	map.setinfo(v3, 1, 0);
	map.setinfo(v4, 1, 1);

	cout << "Display:" << endl;
	map.seemap();

	cout << endl << endl;

	Terrain w("W");
	map.setinfo(w, 0, 0);
	cout << "Display:" << endl;

	map.seemap();

	map.setinfo(v4, 0, 0);
	map.setinfo(v, 1, 1);

	cout << "Display:" << endl;
	map.seemap();


	return 0;
}