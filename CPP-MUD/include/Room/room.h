#ifndef ROOM_HEADER
#define ROOM_HEADER

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <math.h>

using namespace std;

class Room{

    public:

        Room(int id=-1, int x=0, int y=0, string desc="");
        //Room(Room& r);
        virtual ~Room();

        //Var

        //Modifiers
        void initialize();
        inline void setID(int id) {this->roomID = id;};
        inline void setX(int x) {this->xPos = x;};
        inline void setY(int y) {this->yPos = y;};
        bool addPath(int p);
        bool addNeighbor(int dir, int n);

        //Accessors
        virtual void showRoom() const;
        inline int getID() const {return this->roomID;};
        inline int getX() const {return this->xPos;};
        inline int getY() const {return this->yPos;};
        const vector<int> takenDir() const;
        bool hasNeighbor(int id);

    private:

        //Priv-Var
        int roomID;
        int xPos;
        int yPos;

        vector<int> paths;
        int neihbors[8] = {0,0,0,0,0,0,0,0};


        string desc;
        //Priv-Modifiers

        //Priv-Accessors
};
#endif
