#include "header.h"
#include "MapTile.h"
#include "Base.h"

extern int x,y;

MapTile::MapTile(){
	cout << "Map created" << endl;
}

MapTile::~MapTile(){}

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