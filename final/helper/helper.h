#ifndef helper_h  //header guard
#define helper_h  //so it protexts itself not to copy the same header file twice

#include "header.h"
#include "Base.h"
#include "Avatar.h"
#include "helper.h"
#include "MapTile.h"
#include "Vampire.h"
#include "Werewolf.h"
#include "Terrain.h"

int position(vector <Werewolf*> v1 , Base* k);
int position(vector <Vampire*> v1 , Base* k);
bool arguments_line(int a, int b);

#endif
