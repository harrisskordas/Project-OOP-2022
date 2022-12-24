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
        string getname() const;
        void attack(Base* , int );      //alternative   void attack(Base* , int );
        void heal(Base* , int ); 
        int getpotion() const;
        void addpotion();
        void subpotion();
        void sethealth(int );
        int gethealth() const;
        int getshield() const;
        int getstrength() const;
};

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

void Base::addpotion(){
    this->potion = this->potion + 1;
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

class Avatar : public Base{
    public:
        Avatar(string ,int );
        ~Avatar();
};

Avatar::Avatar(string name, int potion){
    this->name = name;
    this->potion = 1;
    cout << "Your Avatar with sign: " << this->name << " just created."<< endl;
    cout << "You have: " << this->potion << " potion."<< endl;
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
        Base* getinfo(int ,int ) const;
		void display() const;
        bool check_terrain(int , int ) const;
        bool check_terrainAV(int , int ) const;
        void getposition(int* ,int*, Base* );
        int getposition(int ,int);	
        bool check_boundaries(int , int ) const;
};

MapTile::MapTile(){
	cout << "Map created" << endl;
}

void MapTile::setinfo(Base* cr, int a, int b){
	this->map[a][b] = cr;
}

Base* MapTile::getinfo(int a, int b) const{
	return this->map[a][b];
}

void MapTile::display() const{
    cout << "Display of the map:" << endl;
	for (int i=0; i<x; i++){
        for (int j=0; j<y; j++)
        {
            cout << this->map[i][j]->getname() << " ";
        }
        cout << endl;
	}
}

bool MapTile::check_terrain(int a, int b) const{
    if((this->map[a][b]->getname()) == "E"){
        return true;
    }else{
        return false;
    }
}

bool MapTile::check_terrainAV(int a, int b) const{
    if(((this->map[a][b]->getname()) == "E") || ((this->map[a][b]->getname()) == "P")){
        return true;
    }else{
        return false;
    }
}

bool MapTile::check_boundaries(int a, int b) const{
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

int MapTile::getposition(int a, int b){     //0 Vampire 1 Werewolf 2 Terrain 3 Avatar(has 1 length...single char)
    int found;
    if(((this->map[a][b]->getname().find("V")) == 0) && ((this->map[a][b]->getname().length() != 1))){
        found=0;
    }else if(((this->map[a][b]->getname().find("W")) == 0) && ((this->map[a][b]->getname().length() != 1))){
        found=1;
    }else if((((this->map[a][b]->getname().find("W") == 0) || (this->map[a][b]->getname().find("V")) == 0)) && (this->map[a][b]->getname().length() == 1)){
        found=3;
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

int position(vector <Werewolf*> v1 , Base* k){
    vector<Werewolf*>::iterator it;
    it = find(v1.begin(), v1.end(), k);
    if(it != v1.end())
        return (it - v1.begin());
    else
        return -1;
}

int position(vector <Vampire*> v1 , Base* k){
    vector<Vampire*>::iterator it;
    it = find(v1.begin(), v1.end(), k);
    if(it != v1.end())
        return (it - v1.begin());
    else
        return -1;
}


int main(int argc, char *argv[]){

    MapTile map;
    Avatar* av;
	vector<Vampire*> vv;
    vector<Werewolf*> vw;
    int water_count, tree_count, creature_count, v_count, w_count;
    int wx, wy;
    int round=0;
    int time_of_day;    //0=day 1=night
    srand((unsigned)time(NULL));

    time_t currentTime=time(NULL);
    tm* timeStruct = localtime(&currentTime);
    cout << "Time of the day at 24hr form: " << timeStruct->tm_hour << endl;

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

    cout << "Dear Player please wait till the map is fully loaded..." << endl;
    sleep(4);   //for mimic loading time of a game

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
    
    //extra potion
    do{
        wx=rand()%(x);
        wy=rand()%(y);
        }while((map.check_terrain(wx,wy)) == false);
    //cout << "Placing extra potion at (" << wx << "," << wy << ")" << endl;
    string strpo = "P";
    Terrain* pot = new Terrain(strpo);
    map.setinfo(pot,wx,wy);

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
    int choice, pmwx,pmwy;
    cin >> choice;
    if (choice == 0){
        cout << "Excellent,you are a Vampire then!You can see your position on the map with a V sign" << endl;
        av = new Avatar("V", 1);    //avatar starts with one potion
        do{
            wx=rand()%(x);
            wy=rand()%(y);
        }while((map.check_terrain(wx,wy)) == false);
    }else{
        cout << "Great choice to be a part of the Werewolves team!You can see your position on the map with a W sign" << endl;
        av = new Avatar("W", 1);    //avatar starts with one potion
        do{
            wx=rand()%(x);
            wy=rand()%(y);
        }while((map.check_terrain(wx,wy)) == false);
    }
    cout << "You are at (" << wx << "," << wy << ")" << endl;
    map.setinfo(av, wx, wy);
    pmwx=wx;
    pmwy=wy;
    cout << "Remember you cannot attack or be attacked.You can only heal the members of your team." << endl;
    cout << "You will be able to move in each round by one position(up,down,left,right)." << endl;
    
    map.display();
    cout << endl << "Every round ends when all creautures have spent their mana." << endl;
    
    while(vv.size()!=0 || vw.size()!=0){
        round++;
        int ch;
        cout << endl << "Round: " << round << endl;
        cout << "Press 1 to continue or 0 to end: ";
        cin >> ch;

        if(ch==1){
            //night or day
            if ((round % 2) == 0){
                time_of_day = 0;    //day
            }else{
                time_of_day = 1;    //night
            }

            if(time_of_day == 1){
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
                    //attack scenario
                    for(int j=-1; j<=1; j++){    //checking row
                        for(int k=-1; k<=1; k++){   //checking column
                            if(j!=0 || k!=0){    //self placed at (0,0)
                                int jj,kk;
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
                                            


                                            //ΔΕΣ ΤΟ ΠΡΙΝ ΤΟ ΔΩΣΕΙΣ πρέπει να διαγράψεις τον δείκτη,object και το σημάδι του από τον χάρτη 
                                            if(x->gethealth() <= 0){    //delete object
                                                string strean = "E"; 
                                                Terrain* ean = new Terrain(strean);
                                                map.setinfo(ean,jj,kk);  //clears the sign at the map and puts object with name"E"
                                                int l = position(vw, x);
                                                //cout << "SOS SOS SOS SOS" << x->getname() << "WILL BE DELETED" << endl;
                                                vw.erase(vw.begin() + l);  //remove this index
                                            }


                                            mana=0;
                                            if(vw.size() == 0){  //vw.size() < 0 ή vw.size() == 0 ?????
                                                cout << "Vampires won!Hurray!" << endl;
                                                for (int i = 0; i < vv.size(); i++){
                                                    delete vv[i]; // Calls ~object and deallocates
                                                }
                                                delete av;
                                                vv.clear(); //clears the vector
                                                vw.clear(); //clears the vector
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
                                    int jj,kk;
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


                    //move scenario
                    if(mana == 1){    //Neither he attacked nor healed a creature,so he is gonna move now

                        cout << "Since " << vv[i]->getname() << " didn't attack or heal,he will now move" << endl;
                        cout << "Vampire with name: " << vv[i]->getname() << " is at " << "(" << mx << "," << my << ")" << endl;

                        for(int j=-1; j<=1; j++){    //checking row
                            if(mana == 0){
                                break;
                            }
                            for(int k=-1; k<=1; k++){   //checking column
                                if(mana == 0){
                                    break;
                                }
                                if(j!=0 || k!=0){    //self placed at (0,0)
                                    int jj,kk;
                                    if(map.check_boundaries(mx-j,my-k) == true){  //the sub happens to connect the -1 position on the map with the -1index of the array

                                        jj = mx-j;
                                        kk = my-k;
                                        //cout << "Searching at: " << "(" << jj << "," << kk << ")" << endl;
                                        if(map.check_terrain(jj,kk) == true){      //Empty space found at (jj,kk) 
                                            map.setinfo(vv[i],jj,kk);     //move pointer of creature
                                            string strean = "E"; 
                                            Terrain* ean = new Terrain(strean);
                                            map.setinfo(ean,mx,my);  //clears the sign at the map and puts object with name"E"
                                            cout << "Vampire with name " << vv[i]->getname() << " will move to " << "(" << jj << "," << kk << ")" << endl;
                                            mana=0;
                                        }else{
                                            //cout << "No Space to move" << endl;
                                        }
                                    }else{
                                        //cout << "Out of bounds" << endl;
                                    }
                                }
                            }
                        }
                    }
                    
                    //finished his turn(attack/heal/move)
                    cout << "Vampire with name " << vv[i]->getname() << " finished his turn." << endl;

                }

                cout << "After all the Vampires finished their turn the map is updated as:" << endl;
                map.display();

            }else{
                cout << "Werewolves will start round: " << round << endl;
                if (time_of_day == 0){
                    cout <<"Time of the day: Day" << endl;
                }else{
                    cout <<"Time of the day: Night" << endl;
                }
                for(int i=0; i<vw.size(); i++){
                    cout << vw[i]->getname() << " is playing..." << endl;
                    cout << vw[i]->getname() << " is searching for enemies..." << endl;

                    int enemies_count=0, allies_count=0, mana=1;    //mana to ensure that if he attacks,then no other move is allowed(heal/move)
                    int mx,my;

                    map.getposition(&mx, &my, vw[i]);   //to know where the vampire is mx=row my=column
                    //cout << "Werewolf with name: " << vw[i]->getname() << " is at " << "(" << mx << "," << my << ")" << endl;
                    
                    //checking all around
                    //attack scenario
                    for(int j=-1; j<=1; j++){    //checking row
                        for(int k=-1; k<=1; k++){   //checking column
                            if(j!=0 || k!=0){    //self placed at (0,0)
                                int jj,kk;
                                if(map.check_boundaries(mx-j,my-k) == true){  //the sub happens to connect the -1 position on the map with the -1index of the array
                                    //cout << "IN" << j << k << endl;
                                    jj = mx-j;
                                    kk = my-k;
                                    //cout << "Searching at: " << "(" << jj << "," << kk << ")" << endl;
                                    if(map.getposition(jj,kk) == 0){      //enemy(Vampire) found 
                                        enemies_count++;
                                        Base* x = map.getinfo(jj,kk);     //two differnet pointers pointing at same object...Base* x = Werewolf* vw[] = Object Werewolf at heap
                                        cout << "Enemy with name " << x->getname() << " is found at " << "(" << jj << "," << kk << ")" << endl;
                                        if((vw[i]->getstrength() >= x->getstrength()) && mana!=0){       //attack
                                            cout << x->getname() << " has health " << x->gethealth() << endl;
                                            cout << vw[i]->getname() << " has strength " << vw[i]->getstrength() << endl;
                                            vw[i]->attack(x, vw[i]->getstrength());
                                            cout << vw[i]->getname() << " is attacking to " << x->getname() << endl;
                                            cout << "After attack " << x->getname() << " has " << x->gethealth() << " health" << endl;
                                            


                                            //ΔΕΣ ΤΟ ΠΡΙΝ ΤΟ ΔΩΣΕΙΣ πρέπει να διαγράψεις τον δείκτη,object και το σημάδι του από τον χάρτη 
                                            if(x->gethealth() <= 0){    //delete object
                                                string strean = "E"; 
                                                Terrain* ean = new Terrain(strean);
                                                map.setinfo(ean,jj,kk);  //clears the sign at the map and puts object with name"E"
                                                int l = position(vw, x);
                                                //cout << "SOS SOS SOS SOS" << x->getname() << "WILL BE DELETED" << endl;
                                                vv.erase(vv.begin() + l);  //remove this index
                                            }


                                            mana=0;
                                            if(vv.size() == 0){  //vv.size() < 0 ή vv.size() == 0 ?????
                                                cout << "Werewolves won!Hurray!" << endl;
                                                for (int i = 0; i < vw.size(); i++){
                                                    delete vw[i]; // Calls ~object and deallocates
                                                }
                                                delete av;
                                                vv.clear(); //clears the vector
                                                vw.clear(); //clears the vector
                                                return 0;
                                            }
                                        }else{
                                            cout << vw[i]->getname() << " has " << vw[i]->getstrength() << " strength." << x->getname() << " has " << x->getstrength()  << " strenth." << endl;
                                            cout << vw[i]->getname() << " didn't attack to " << x->getname() << ",because " << x->getname() << " has more strength" << " or " << vw[i]->getname() << " is out of mana." <<endl;
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
                    if((mana == 1) && (vw[i]->getpotion()>0)){    //and IF HE HAS enough potion

                        cout << "Since " << vw[i]->getname() << " didn't attack,he will now search for nearby allies to help" << endl;
                        cout << vw[i]->getname() << " has " << vw[i]->getpotion() << " potion" << endl;
                        cout << vw[i]->getname() << " is searching for allies..." << endl;

                        for(int j=-1; j<=1; j++){    //checking row
                            for(int k=-1; k<=1; k++){   //checking column
                                if(j!=0 || k!=0){    //self placed at (0,0)
                                    int jj,kk;
                                    if(map.check_boundaries(mx-j,my-k) == true){  //the sub happens to connect the -1 position on the map with the -1index of the array
                                        //cout << "IN" << j << k << endl;
                                        jj = mx-j;
                                        kk = my-k;
                                        //cout << "Searching at: " << "(" << jj << "," << kk << ")" << endl;
                                        if(map.getposition(jj,kk) == 1){      //allie(Werewolf) found 
                                            allies_count++;
                                            Base* x = map.getinfo(jj,kk);     //two differnet pointers pointing at same object...Base* x = Werewolf* vw[] = Object Werewolf at heap
                                            cout << "Allie with name " << x->getname() << " is found at " << "(" << jj << "," << kk << ")" << endl;

                                            if((x->gethealth() != 2) && mana!=0){       //if the allie hasn't full health
                                                mana=0;
                                                cout << x->getname() << " has health " << x->gethealth() << endl;
                                                vw[i]->heal(x, -1); //for heal we have damage = -1...so it becomes   this->health = this->health - (-damage);
                                                cout << vw[i]->getname() << " is healing " << x->getname() << endl;
                                                cout << "After heal " << x->getname() << " has " << x->gethealth() << " health" << endl;
                                            }else{
                                                cout << vw[i]->getname() << " has " << vw[i]->getpotion() << " potion(s)." << x->getname() << " has " << x->gethealth()  << " health." << endl;
                                                cout << vw[i]->getname() << " didn't heal " << x->getname() << ",because " << x->getname() << " has full health." << endl;
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
                        cout << vw[i]->getname() << " has " << vw[i]->getpotion() << " potion." << endl;
                        cout << vw[i]->getname() << " has " << mana << " mana." << endl;
                        cout << vw[i]->getname() << " hasn't enough potion or " << vw[i]->getname() << " is out of mana to start searching for allies to help" << endl;
                    }


                    //move scenario
                    if(mana == 1){    //Neither he attacked nor healed a creature,so he is gonna move now

                        cout << "Since " << vw[i]->getname() << " didn't attack or heal,he will now move" << endl;
                        cout << "Werewolf with name: " << vw[i]->getname() << " is at " << "(" << mx << "," << my << ")" << endl;

                        for(int j=-1; j<=1; j++){    //checking row
                            if(mana == 0){
                                break;
                            }
                            for(int k=-1; k<=1; k++){   //checking column
                                if(mana == 0){
                                    break;
                                }
                                if(j!=0 || k!=0){    //self placed at (0,0)
                                    int jj,kk;
                                    if(map.check_boundaries(mx-j,my-k) == true){  //the sub happens to connect the -1 position on the map with the -1index of the array

                                        jj = mx-j;
                                        kk = my-k;
                                        //cout << "Searching at: " << "(" << jj << "," << kk << ")" << endl;
                                        if(map.check_terrain(jj,kk) == true){      //Empty space found at (jj,kk) 
                                            map.setinfo(vw[i],jj,kk);     //move pointer of creature
                                            string strean = "E"; 
                                            Terrain* ean = new Terrain(strean);
                                            map.setinfo(ean,mx,my);  //clears the sign at the map and puts object with name"E"
                                            cout << "Werewolf with name " << vw[i]->getname() << " will move to " << "(" << jj << "," << kk << ")" << endl;
                                            mana=0;
                                        }else{
                                            //cout << "No Space to move" << endl;
                                        }
                                    }else{
                                        //cout << "Out of bounds" << endl;
                                    }
                                }
                            }
                        }
                    }
                    
                    //finished his turn(attack/heal/move)
                    cout << "Werewolf with name " << vw[i]->getname() << " finished his turn." << endl;

                }

                cout << "After all the Werewolves finished their turn the map is updated as:" << endl;
                map.display();
            }

            //AVATAR Player turn is now
                char whereTo;
                int whatTo;
                int allies=0,manaa=1;
                cout << "Time of the day: " << time_of_day << endl;
                cout << "Now it is your turn to play!Here are your stats:" << endl;
                cout << "Your position: (" << pmwx << "," << pmwy << ")" << endl;
                cout << "Potion: " << av->getpotion() << endl;
                cout << "Mana: " << manaa << endl;
                if(choice == 0){
                    cout << "Number of allies(Vampires) total: " << vv.size() << endl;
                    if(vv.size() == 0){
                        cout << "Your team lost.Noone survived to help." << endl;
                        break;  //end of big while
                    }
                }else{
                    cout << "Number of allies(Werewolves) total: " << vw.size() << endl;
                    if(vw.size() == 0){
                        cout << "Your team lost.Noone survived to help." << endl;
                        break;  //end of big while
                    }
                }
                for(int j=-1; j<=1; j++){    //checking row
                    for(int k=-1; k<=1; k++){   //checking column
                        if(j!=0 || k!=0){    //self placed at (0,0)
                            int jj,kk;
                            if(map.check_boundaries(pmwx-j,pmwy-k) == true){  //the sub happens to connect the -1 position on the map with the -1index of the array
                                //cout << "IN" << j << k << endl;
                                jj = pmwx-j;
                                kk = pmwy-k;
                                //cout << "Searching at: " << "(" << jj << "," << kk << ")" << endl;
                                if(map.getposition(jj,kk) == 0 && choice == 0){      //allie(Vampire) found 
                                    allies++;
                                }
                                if(map.getposition(jj,kk) == 1 && choice == 1){      //allie(Werewolf) found 
                                    allies++;
                                }
                            }else{
                                //cout << "Out of bounds" << endl;
                            }
                        }
                    }
                }
                cout << "Number of allies around you: " << allies << endl;
                while(manaa!=0){
                    if(allies>0){
                        do{
                        cout << "Type 1 to choose healing a teammate or 0 to move: ";
                        cin >> whatTo;
                        }while(whatTo!=0 && whatTo!=1);
                    }
                    if(whatTo==0 || allies==0 || av->getpotion()==0){
                        if(manaa==0){
                            break;
                        }
                        if(allies==0){
                            cout << "Since you have no allies around you or potion(s),you will move." << endl;
                        }
                        cout << "Choose where you want to go(W=up,D=right,A=left,S=down): ";
                        cin >> whereTo;
                        int flag=true;
                        while(flag==true){
                            if((whereTo == 'W') && (map.check_boundaries(pmwx-1,pmwy) == true) && (map.check_terrainAV(pmwx-1,pmwy) == true)){      //Empty and valid space found at (pmwx-1,pmwy)){
                                if(map.getinfo(pmwx-1,pmwy)->getname() == "P"){
                                    av->addpotion();
                                    cout << "Congratulations.You found the extra potion on the map." << endl;
                                }
                                map.setinfo(av,pmwx-1,pmwy);     //move pointer of creature
                                string strean = "E"; 
                                Terrain* ean = new Terrain(strean);
                                map.setinfo(ean,pmwx,pmwy);  //clears the sign at the map and puts object with name"E"
                                pmwx=pmwx-1;
                                cout << "Your new position is: (" << pmwx << "," << pmwy << ")" << endl;
                                flag=false;
                            }else if((whereTo == 'D') && (map.check_boundaries(pmwx,pmwy+1) == true) && (map.check_terrainAV(pmwx,pmwy+1) == true)){      //Empty and valid space found at (pmwx-1,pmwy)){
                                if(map.getinfo(pmwx,pmwy+1)->getname() == "P"){
                                    av->addpotion();
                                    cout << "Congratulations.You found the extra potion on the map." << endl;
                                }
                                map.setinfo(av,pmwx,pmwy+1);     //move pointer of creature
                                string strean = "E"; 
                                Terrain* ean = new Terrain(strean);
                                map.setinfo(ean,pmwx,pmwy);  //clears the sign at the map and puts object with name"E"
                                pmwy=pmwy+1;
                                cout << "Your new position is: (" << pmwx << "," << pmwy << ")" << endl;
                                flag=false;
                            }else if((whereTo == 'A') && (map.check_boundaries(pmwx,pmwy-1) == true) && (map.check_terrainAV(pmwx,pmwy-1) == true)){      //Empty and valid space found at (pmwx-1,pmwy)){
                                if(map.getinfo(pmwx,pmwy-1)->getname() == "P"){
                                    av->addpotion();
                                    cout << "Congratulations.You found the extra potion on the map." << endl;
                                }
                                map.setinfo(av,pmwx,pmwy-1);     //move pointer of creature
                                string strean = "E"; 
                                Terrain* ean = new Terrain(strean);
                                map.setinfo(ean,pmwx,pmwy);  //clears the sign at the map and puts object with name"E"
                                pmwy=pmwy-1;
                                cout << "Your new position is: (" << pmwx << "," << pmwy << ")" << endl;
                                flag=false;
                            }else if((whereTo == 'S') && (map.check_boundaries(pmwx+1,pmwy) == true) && (map.check_terrainAV(pmwx+1,pmwy) == true)){      //Empty and valid space found at (pmwx-1,pmwy)){
                                if(map.getinfo(pmwx+1,pmwy)->getname() == "P"){
                                    av->addpotion();
                                    cout << "Congratulations.You found the extra potion on the map." << endl;
                                }
                                map.setinfo(av,pmwx+1,pmwy);     //move pointer of creature
                                string strean = "E"; 
                                Terrain* ean = new Terrain(strean);
                                map.setinfo(ean,pmwx,pmwy);  //clears the sign at the map and puts object with name"E"
                                pmwx=pmwx+1;
                                cout << "Your new position is: (" << pmwx << "," << pmwy << ")" << endl;
                                flag=false;
                            }else{
                                cout << "The position you tried to reach is not valid.Choose again where you want to go(W=up,D=right,A=left,S=down): ";
                                cin >> whereTo;
                                sleep(4);
                            }
                        }
                        manaa=0;
                        }else{
                        for(int j=-1; j<=1; j++){    //checking row
                            if (manaa==0){
                                break;
                            }
                            for(int k=-1; k<=1; k++){   //checking column
                                if (manaa==0){
                                    break;
                                }
                                if(j!=0 || k!=0){    //self placed at (0,0)
                                    int jj,kk;
                                    if(map.check_boundaries(pmwx-j,pmwy-k) == true){      //the sub happens to connect the -1 position on the map with the -1index of the array
                                        //cout << "IN" << j << k << endl;
                                        jj = pmwx-j;
                                        kk = pmwy-k;
                                        //cout << "Searching at: " << "(" << jj << "," << kk << ")" << endl;
                                        if(map.getposition(jj,kk) == 0 && choice == 0){      //allie(Vampire) found 
                                            allies++;
                                        }
                                        if(map.getposition(jj,kk) == 1 && choice == 1){      //allie(Werewolf) found 
                                            allies++;
                                        }
                                        if((map.getposition(jj,kk) == 0 && choice == 0) || (map.getposition(jj,kk) == 1 && choice == 1)){      //allie(Vampire) found
                                            cout << "Allie found at: " << "(" << jj << "," << kk << ")" << endl;
                                            Base* x = map.getinfo(jj,kk);     //two differnet pointers pointing at same object...Base* x = Werewolf* vw[] = Object Werewolf at heap
                                            cout << "Allie with name " << x->getname() << " has health " << x->gethealth() << endl;
                                            if(x->gethealth()==2){
                                                cout << "Allie with name " << x->getname() << " has full health,so you cannot heal him." << endl;
                                            }else{  //not full health
                                                cout << "Do you want to heal him by 1 health?Doing so you will not bea able to move." << endl;
                                                string ans;
                                                cin >> ans;
                                                if(ans.compare("yes")==0){
                                                    manaa=0;
                                                    cout << "You are healing " << x->getname() << endl;
                                                    av->subpotion();
                                                    x->sethealth(-1);
                                                    cout << "After healing " << x->getname() << " has health " << x->gethealth() << endl;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }else{
                cout << "You ended the game" << endl;
                break;
            }
        }//end of while/end of game

    map.display();
    

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