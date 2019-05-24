#ifndef MAP_HEADER
#define MAP_HEADER

#include "../Room/room.h"
#include <vector>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <iterator>

using namespace std;

class Map{

    public:

        Map(int id=-1, int size=0);
        virtual ~Map();

        //Var


        //Modifiers
        void generateMap(const int size);
        vector<shared_ptr<Room>>::iterator getRoom(int x, int y);
        int getRoomIndex (int id);
        int getRoomIndex (int x, int y);

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

        vector<shared_ptr<Room>> rooms;

        //Priv-Modifiers


        //Priv-Accessors
};
#endif
