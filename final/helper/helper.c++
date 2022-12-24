#include "helper.h"
#include "MapTile.h"
#include "header.h"

extern int x,y;

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

bool arguments_line(int a, int b){
    if (a<0){
        cout << "Vertical axis cannot be 0 or negative";
        return false;
    }
    if (b<0){
        cout << "Horizontal axis cannot be 0 or negative";
        return false;
    }

    return true;
}
