#ifndef MapTile_h  //header guard
#define MapTile_h  //so it protexts itself not to copy the same header file twice

#include "header.h"
#include "Base.h"

class MapTile{
	private:
		Base* map[1000][1000];
	public:
		MapTile();
        ~MapTile();
		void setinfo(Base* , int , int );
        Base* getinfo(int ,int ) const;
		void display() const;
        bool check_terrain(int , int ) const;
        bool check_terrainAV(int , int ) const;
        void getposition(int* ,int*, Base* );
        int getposition(int ,int);	
        bool check_boundaries(int , int ) const;
};

#endif