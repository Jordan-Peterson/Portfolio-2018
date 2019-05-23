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

        Room(int id=-1, int x=0, int y=0, string desc="",bool n=false, bool ne=false, bool nw=false, bool e=false, bool w=false, bool s=false, bool se=false, bool sw=false);
        //Room(Room& r);
        virtual ~Room();

        //Var

        //Modifiers
        void initialize();
        inline void setID(int id) {this->roomID = id;};
        inline void setX(int x) {this->xPos = x;};
        inline void setY(int y) {this->yPos = y;};
        inline void setNorth(bool n) {this->north = n;};
        inline void setNorthEast(bool ne) {this->northeast = ne;};
        inline void setNorthWest(bool nw) {this->northwest = nw;};
        inline void setEast(bool e) {this->east = e;};
        inline void setWest(bool w) {this->west = w;};
        inline void setSouth(bool s) {this->south = s;};
        inline void setSouthEast(bool se) {this->southeast = se;};
        inline void setSouthWest(bool sw) {this->southwest = sw;};

        //Accessors
        virtual void showRoom() const;
        inline int getID() const {return this->roomID;};
        inline int getX() const {return this->xPos;};
        inline int getY() const {return this->yPos;};
        inline bool hasNorth() const {return this->north;};
        inline bool hasNorthEast() const {return this->northeast;};
        inline bool hasNorthWest() const {return this->northwest;};
        inline bool hasEast() const {return this->east;};
        inline bool hasWest() const {return this->west;};
        inline bool hasSouth() const {return this->south;};
        inline bool hasSouthEast() const {return this->southeast;};
        inline bool hasSouthWest() const {return this->southwest;};
        const vector<int> availableDir() const;
        bool roomTaken(int x, int y) const;

    private:

        //Priv-Var
        int roomID;
        int xPos;
        int yPos;

        bool north;
        bool east;
        bool south;
        bool west;
        bool northwest;
        bool northeast;
        bool southeast;
        bool southwest;


        string desc;
        //Priv-Modifiers

        //Priv-Accessors
};
#endif
