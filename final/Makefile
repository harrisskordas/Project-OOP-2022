OBJS	= project.o Terrain.o Vampire.o Werewolf.o MapTile.o helper.o Base.o Avatar.o
SOURCE	= project.c++ Terrain.c++ Vampire.c++ Werewolf.c++ MapTile.c++ helper.c++ Base.c++ Avatar.c++
HEADER	= Terrain.h Vampire.h Werewolf.h MapTile.h helper.h header.h Base.h Avatar.h
OUT	= a.out
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

project.o: project.c++
	$(CC) $(FLAGS) project.c++

Terrain.o: Terrain.c++
	$(CC) $(FLAGS) Terrain.c++

Vampire.o: Vampire.c++
	$(CC) $(FLAGS) Vampire.c++

Werewolf.o: Werewolf.c++
	$(CC) $(FLAGS) Werewolf.c++

MapTile.o: MapTile.c++
	$(CC) $(FLAGS) MapTile.c++

helper.o: helper.c++
	$(CC) $(FLAGS) helper.c++

Base.o: Base.c++
	$(CC) $(FLAGS) Base.c++

Avatar.o: Avatar.c++
	$(CC) $(FLAGS) Avatar.c++


clean:
	rm -f $(OBJS) $(OUT)