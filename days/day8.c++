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
        int strength;
        int shield;
    public:
        string getname();
        void attack(Base* , int );      //alternative   void attack(Base* , int );
        void heal(Base* , int ); 
        int getpotion();
        void addpotion();
        void subpotion();
        void sethealth(int );
        int gethealth();
        int getshield();
        int getstrength();
};

void Base::attack(Base* crea, int damage){    //alternative void attack(Base* , int ); crea->
    crea->sethealth(damage);
}

void Base::heal(Base* crea, int damage){    //alternative void attack(Base* , int ); crea->
    crea->sethealth(damage);
}

string Base::getname(){
    return this->name;
}

int Base::getpotion(){
    return this->potion;
}

void Base::addpotion(){
    this->potion = this->potion + 1;
}

void Base::subpotion(){
    this->potion = this->potion - 1;
}

void Base::sethealth(int damage){   //for heal we have damage = -1...so it becomes   this->health = this->health - (-damage);
    this->health = this->health - damage;
}

int Base::gethealth(){
    return this->health;
}

int Base::getshield(){
    return this->shield;
}

int Base::getstrength(){
    return this->strength;
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
        Vampire(string ,int ,int, int, int);
        ~Vampire();
};

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

class Werewolf : public Base{
    public:
        Werewolf(string ,int ,int, int, int);
        ~Werewolf();
};

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
        Base* getinfo(int ,int );
		void display();
        bool check_terrain(int , int );
        void getposition(int* ,int*, Base* );
        int getposition(int ,int);	
        bool check_boundaries(int , int );	
};

MapTile::MapTile(){
	cout << "Map created" << endl;
}

void MapTile::setinfo(Base* cr, int a, int b){
	this->map[a][b] = cr;
}

Base* MapTile::getinfo(int a, int b){
	return this->map[a][b];
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

/*bool MapTile::check_boundaries(int a, int b){
    if(a<0 || a>x || b<0 || b>y){
        return false;       //out of bounds
    }else{
        if(this->map[a][b]->getname() == "E" || this->map[a][b]->getname() == "A" || this->map[a][b]->getname() == "T" || this->map[a][b]->getname().find("V") != -1 || this->map[a][b]->getname().find("W") != -1){
            return true;
        }
    }
    return false;   //in bounds but nothing found
}*/

bool MapTile::check_boundaries(int a, int b){
    //cout << "a:" << a << "b:" << b << endl;
    if(a>=x || b>=y){
        return false;       //out of bounds
    }else if(a<0 || b<0){
        return false;
    }else{
        return true;
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

int MapTile::getposition(int a, int b){     //0 Vampire 1 Werewolf 2 Terrain/Avatar
    int found;
    if((this->map[a][b]->getname().find("V")) == 0){
        found=0;
    }else if((this->map[a][b]->getname().find("W")) == 0){
        found=1;
    }else{
        found=2;
    }
    return found;
}

int vecfind(vector<Base*> vec, Base* x){
    for(int i=0; i<vec.size(); i++){
        if(vec[i] == x){
            return i;
        }
    }
    return -1;
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
        int hp,strength,pot,shield;
        pot = rand()%(2);
        strength = rand()%(3)+1;
        shield = rand()%(2)+1;
        hp = 2;
        Vampire* v = new Vampire(strv, pot, hp, strength, shield);       //(string name, int potion, int health, int strength, int shield)
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
        int hp,strength,pot,shield;
        pot = rand()%(2);
        strength = rand()%(3)+1;
        shield = rand()%(2)+1;
        hp = 2;
        Werewolf* w = new Werewolf(strw, pot, hp, strength, shield);
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
    cout << endl << "Every round ends when all creautures have spent their mana." << endl;
    
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

            int enemies_count=0, allies_count=0, mana=1;    //mana to ensure that if he attacks,then no other move is allowed(heal/move)
            int mx,my;

            map.getposition(&mx, &my, vv[i]);   //to know where the vampire is mx=row my=column
            //cout << "Vampire with name: " << vv[i]->getname() << " is at " << "(" << mx << "," << my << ")" << endl;
            
            //checking all around
            for(int j=-1; j<=1; j++){    //checking row
                for(int k=-1; k<=1; k++){   //checking column
                    if(j!=0 || k!=0){    //self placed at (0,0)
                        int check_bounds,jj,kk;
                        if(map.check_boundaries(mx-j,my-k) == true){  //the sub happens to connect the -1 position on the map with the -1index of the array
                            //cout << "IN" << j << k << endl;
                            jj = mx-j;
                            kk = my-k;
                            //cout << "Searching at: " << "(" << jj << "," << kk << ")" << endl;
                            if(map.getposition(jj,kk) == 1){      //enemy(Werewolf) found 
                                enemies_count++;
                                Base* x = map.getinfo(jj,kk);     //two differnet pointers pointing at same object...Base* x = Werewolf* vw[] = Object Werewolf at heap
                                cout << "Enemy with name " << x->getname() << " is found at " << "(" << jj << "," << kk << ")" << endl;
                                if((vv[i]->getstrength() >= x->getstrength()) && mana!=0){       //attack
                                    cout << x->getname() << " has health " << x->gethealth() << endl;
                                    cout << vv[i]->getname() << " has strength " << vv[i]->getstrength() << endl;
                                    vv[i]->attack(x, vv[i]->getstrength());
                                    cout << vv[i]->getname() << " is attacking to " << x->getname() << endl;
                                    cout << "After attack " << x->getname() << " has " << x->gethealth() << " health" << endl;
                                    
                                    
                                    if(x->gethealth() <= 0){    //delete object
                                        //vw.ersase();  //remove this index
                                        //delete x;
                                    
                                    
                                    }
                                    mana=0;
                                    if(vw.size() == 0){  //vw.size() < 0 ή vw.size() == 0 ?????
                                        cout << "Vampires won!Hurray!" << endl;
                                        return 0;
                                    }
                                }else{
                                    cout << vv[i]->getname() << " has " << vv[i]->getstrength() << " strength." << x->getname() << " has " << x->getstrength()  << " strenth." << endl;
                                    cout << vv[i]->getname() << " didn't attack to " << x->getname() << ",because " << x->getname() << " has more strength" << " or " << vv[i]->getname() << " is out of mana." <<endl;
                                }
                            }
                        }else{
                            //cout << "Out of bounds" << endl;
                        }
                    }
                }
            }
            cout << "Enemies nearby: " << enemies_count << endl;

            //heal scenario
            if((mana == 1) && (vv[i]->getpotion()>0)){    //and IF HE HAS enough potion

                cout << "Since " << vv[i]->getname() << " didn't attack,he will now search for nearby allies to help" << endl;
                cout << vv[i]->getname() << " has " << vv[i]->getpotion() << " potion" << endl;
                cout << vv[i]->getname() << " is searching for allies..." << endl;

                for(int j=-1; j<=1; j++){    //checking row
                for(int k=-1; k<=1; k++){   //checking column
                    if(j!=0 || k!=0){    //self placed at (0,0)
                        int check_bounds,jj,kk;
                        if(map.check_boundaries(mx-j,my-k) == true){  //the sub happens to connect the -1 position on the map with the -1index of the array
                            //cout << "IN" << j << k << endl;
                            jj = mx-j;
                            kk = my-k;
                            //cout << "Searching at: " << "(" << jj << "," << kk << ")" << endl;
                            if(map.getposition(jj,kk) == 0){      //allie(Vampire) found 
                                allies_count++;
                                Base* x = map.getinfo(jj,kk);     //two differnet pointers pointing at same object...Base* x = Werewolf* vw[] = Object Werewolf at heap
                                cout << "Allie with name " << x->getname() << " is found at " << "(" << jj << "," << kk << ")" << endl;

                                if((x->gethealth() != 2) && mana!=0){       //if the allie hasn't full health
                                    mana=0;
                                    cout << x->getname() << " has health " << x->gethealth() << endl;
                                    vv[i]->heal(x, -1); //for heal we have damage = -1...so it becomes   this->health = this->health - (-damage);
                                    cout << vv[i]->getname() << " is healing " << x->getname() << endl;
                                    cout << "After heal " << x->getname() << " has " << x->gethealth() << " health" << endl;
                                }else{
                                    cout << vv[i]->getname() << " has " << vv[i]->getpotion() << " potion(s)." << x->getname() << " has " << x->gethealth()  << " health." << endl;
                                    cout << vv[i]->getname() << " didn't heal " << x->getname() << ",because " << x->getname() << " has full health." << endl;
                                }
                            }
                        }else{
                            //cout << "Out of bounds" << endl;
                        }
                    }
                }
            }
            cout << "Allies nearby: " << allies_count << endl;
            }else{
                cout << vv[i]->getname() << " has " << vv[i]->getpotion() << " potion." << endl;
                cout << vv[i]->getname() << " has " << mana << " mana." << endl;
                cout << vv[i]->getname() << " hasn't enough potion or " << vv[i]->getname() << " is out of mana to start searching for allies to help" << endl;
            }
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
}