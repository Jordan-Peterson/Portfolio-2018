#ifndef MAP_HEADER
#define MAP_HEADER

#include "Rooms/room.h"
#include <vector>
#include <stdlib.h>
#include <iostream>

using namespace std;

class Map{

    public:

        Map(int id=-1, int size=0);
        virtual ~Map();

        //Var


        //Modifiers
        void generateMap(const int size);
        vector<Room>::iterator getRoom(int x, int y);

        //Accessors
        bool roomTaken(int x, int y);
        void showMap();

    private:

        //Priv-Var
        int mapID;
        int size;
        int xDim;
        int yDim;
        int numHostile;
        int numPeaceful;

        vector<Room> rooms;

        //Priv-Modifiers


        //Priv-Accessors
};

#endif