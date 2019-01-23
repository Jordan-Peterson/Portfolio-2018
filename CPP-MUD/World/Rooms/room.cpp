#include "room.h"

//=========
//CONSTRUCT
//=========
Room::Room(int id, int x, int y, string desc,bool n, bool ne, bool nw, bool e, bool w, bool s, bool se, bool sw){
    this->north = n;
    this->northeast = ne;
    this->northwest = nw;
    this->east = e;
    this->west = w;
    this->south = s;
    this->southeast = se;
    this->southwest = sw;
    this->xPos = x;
    this->yPos = y;
    this->desc = desc;
    this->roomID = id;
}

// Room::Room(Room& r){
//     this->roomID = r.getID();
//     this->xPos = r.getX();
//     this->yPos = r.getY();
//     this->north = r.north;
//     this->northeast = r.northeast;
//     this->northwest = r.northwest;
//     this->east = r.east;
//     this->west = r.west;
//     this->south = r.south;
//     this->southeast = r.southeast;
//     this->southwest = r.southwest;
//     this->desc = r.desc;
// }

Room::~Room(){

}

//+++++++++
//MODIFIERS
//---------

//=========
//ACCESSORS
//=========
void Room::showRoom() const{
    
}

const vector<int> Room::availableDir() const{
    vector<int> spaces;
    //not efficient, but who cares
    if(!hasNorth()){spaces.push_back(0);}
    if(!hasEast()){spaces.push_back(1);}
    if(!hasSouth()){spaces.push_back(2);}
    if(!hasWest()){spaces.push_back(3);}
    if(!hasNorthWest()){spaces.push_back(4);}
    if(!hasNorthEast()){spaces.push_back(5);}
    if(!hasSouthEast()){spaces.push_back(6);}
    if(!hasSouthWest()){spaces.push_back(7);}
    
    return spaces;
}

//++++++++++++++
//PRIV-MODIFIERS
//--------------

//==============
//PRIV-ACCESSORS
//==============