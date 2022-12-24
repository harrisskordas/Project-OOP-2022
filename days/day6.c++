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

int x,y;

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

class Avatar : public Base{
    public:
        Avatar(string );
        ~Avatar();
};

Avatar::Avatar(string name){
    this->name = name;
    cout << "Your Avatar with sign: " << this->name << " just created."<< endl;
}

Avatar::~Avatar(){
    cout << "Your avatar is destroyed!"<< endl;
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
		Base* map[1000][1000];
	public:
		MapTile();
		void setinfo(Base* , int , int );
		void display();
        bool check_terrain(int , int );
        void getposition(int* ,int*, Base* );
        int getposition(int ,int);		
};

MapTile::MapTile(){
	cout << "Map created" << endl;
}

void MapTile::setinfo(Base* cr, int a, int b){
	this->map[a][b] = cr;
}

void MapTile::display(){
    cout << "Display of the map:" << endl;
	for (int i=0; i<x; i++){
        for (int j=0; j<y; j++)
        {
            cout << this->map[i][j]->getname() << " ";
        }
        cout << endl;
	}
}

bool MapTile::check_terrain(int a, int b){
    if((this->map[a][b]->getname()) == "E"){
        return true;
    }else{
        return false;
    }
}

void MapTile::getposition(int* a, int* b, Base* cre){
    for(int i=0; i<x; i++){
        for(int j=0; j<y; j++){
            if (this->map[i][j] == cre){
                *a = i;
                *b = j;
            }
        }
    }
}

int MapTile::getposition(int a, int b){     //0 Vampire 1 Werewolf 2 Terrain
    int found;
    if((this->map[a][b]->getname().find("V")) > -1){
        found=0;
    }else if((this->map[a][b]->getname().find("W")) > -1){
        found=1;
    }else{
        found=2;
    }
    return found;
}


int main(int argc, char *argv[]){

    if (argc != 3){
        cout << "Please give dimensions(x,y) of the map";
        return 1;
    }

    x = atoi(argv[1]);
    if (x<=0){
        cout << "Vertical axis cannot be 0 or negative";
        return 1;
    }

    y = atoi(argv[2]);
    if (y<=0){
        cout << "Horizontal axis cannot be 0 or negative";
        return 1;
    }

    MapTile map;
    Avatar* av;
	vector<Vampire*> vv;
    vector<Werewolf*> vw;
    int water_count, tree_count, creature_count, v_count, w_count;
    int wx, wy;
    int first_play, round=0;
    int time_of_day;    //0=day 1=night
    srand((unsigned)time(NULL));

    cout << "Dear Player please wait till the map is fully loaded..." << endl;

    //initialize the map
    for(int i=0; i<x; i++){
        for (int j=0;j<y; j++){
            string strea = "E";
            Terrain* ea = new Terrain(strea);
            map.setinfo(ea,i,j);
        }
    }

    water_count = ((x*y)/20) + 1;
    tree_count = water_count + 1;

    for(int i=0; i<water_count; i++){
        do{
        wx=rand()%(x);
        wy=rand()%(y);
        }while((map.check_terrain(wx,wy)) == false);
        //cout << "Placing water at (" << wx << "," << wy << ")" << endl;
        string strw = "A";
        Terrain* wat = new Terrain(strw);
        map.setinfo(wat,wx,wy);
    }

    for(int i=0; i<tree_count; i++){
        do{
        wx=rand()%(x);
        wy=rand()%(y);
        }while((map.check_terrain(wx,wy)) == false);
        //cout << "Placing tree at (" << wx << "," << wy << ")" << endl;
        string strtr = "T";
        Terrain* wtr = new Terrain(strtr);
        map.setinfo(wtr,wx,wy);
    }

    //map.display();

    creature_count = (x*y)/15;
    v_count = creature_count;
    w_count = creature_count;

    cout << "Number of vampires and werewolves: " << creature_count << " each" << endl;
    for(int i=0; i<creature_count; i++){
        do{
        wx=rand()%(x);
        wy=rand()%(y);
        }while((map.check_terrain(wx,wy)) == false);
        //cout << "Placing Vampire at (" << wx << "," << wy << ")" << endl;
        string strv = "V";
        strv = strv + to_string(i);
        Vampire* v = new Vampire(strv, 2, 2);
        map.setinfo(v, wx, wy);
        vv.push_back(v);
    }

    for(int i=0; i<creature_count; i++){
        do{
        wx=rand()%(x);
        wy=rand()%(y);
        }while((map.check_terrain(wx,wy)) == false);
        //cout << "Placing Werewolf at (" << wx << "," << wy << ")" << endl;
        string strw = "W";
        strw = strw + to_string(i);
        Werewolf* w = new Werewolf(strw, 2, 2);
        map.setinfo(w, wx, wy);
        vw.push_back(w);
    }

    map.display();


    cout << "Number of vampires: " << v_count << endl;
    cout << "Number of werewolves: " << w_count << endl;
    cout << "All set.Shall we begin?To start choose if you want to be a Vampire or Werewolf by typing the creature: " << endl;

    //tune in for reading chars
    int choice;
    cin >> choice;
    if (choice == 0){
        cout << "Excellent,you are a Vampire then!You can see your position on the map with a V sign" << endl;
        av = new Avatar("V");
        do{
            wx=rand()%(x);
            wy=rand()%(y);
        }while((map.check_terrain(wx,wy)) == false);
        cout << "You are at (" << wx << "," << wy << ")" << endl;
        map.setinfo(av, wx, wy);
    }else{
        cout << "Great choice to be a part of the Werewolves team!You can see your position on the map with a W sign" << endl;
        av = new Avatar("W");
        do{
            wx=rand()%(x);
            wy=rand()%(y);
        }while((map.check_terrain(wx,wy)) == false);
        cout << "You are at (" << wx << "," << wy << ")" << endl;
        map.setinfo(av, wx, wy);
    }
    cout << "Remember you cannot attack or be attacked.You can only heal the members of your team." << endl;
    
    map.display();
    cout << endl << "Every round ends when all creautures have been given the ability to move." << endl;
    
    //oso den exei xasei kaneis while...
    round++;
    cout << endl << "Round: " << round << endl;

    //night or day
    if ((round % 2) == 0){
        time_of_day = 0;    //day
    }else{
        time_of_day = 1;    //night
    }

    first_play = rand()%(10);
    if(first_play < 5){
        cout << "Vampires will start round: " << round << endl;
        if (time_of_day == 0){
            cout <<"Time of the day: Day" << endl;
        }else{
            cout <<"Time of the day: Night" << endl;
        }
        for(int i=0; i<vv.size(); i++){
            cout << vv[i]->getname() << " is playing..." << endl;
            cout << vv[i]->getname() << " is searching for enemies..." << endl;

            int enemies_count = 0;
            int mx,my;
            map.getposition(&mx, &my, vv[i]);   //to know where the vampire is mx=row my=column
            //cout << "Vampire with name: " << vv[i]->getname() << " is at " << "(" << mx << "," << my << ")" << endl;

            //class funtion to do--mapTile/Base maybe??







            cout << "Enemies: " << enemies_count << endl;
            
        }
    }else{
        cout << "Werewolves will start round: " << round << endl;
    }




    //telos tis while
    for (int i = 0; i < vv.size(); i++) {
        delete vv[i]; // Calls ~object and deallocates
    }

    for (int i = 0; i < vw.size(); i++) {
        delete vw[i]; // Calls ~object and deallocates
    }

    delete av;

    vv.clear(); //clears the vector
    vw.clear(); //clears the vector
	return 0;
}