#include "../../include/Room/room.h"

//=========
//CONSTRUCT
//=========
Room::Room(int id, int x, int y, string desc){
    this->xPos = x;
    this->yPos = y;
    this->desc = desc;
    this->roomID = id;
}

Room::~Room(){

}

//+++++++++
//MODIFIERS
//---------
bool Room::addPath(int p){
    if(p >=0 && p <= 7){
        this->paths.push_back(p);
        return true;
    }
    printf("failed to add path %d\n",p);
    return false;
}

bool Room::addNeighbor(int d, int n){
    if(n >= 0 && d <=7){
        this->neihbors[d] = n;
        return true;
    }
    printf("failed to add neighbor %d to path %d\n",n,d);
    return false;
}

//=========
//ACCESSORS
//=========
void Room::showRoom() const{
    printf("====================\n");
    printf("RoomID: %d\n",this->roomID);
    printf("Coords: (%d,%d)\n",this->xPos,this->yPos);
    printf("Taken: ");
    for(auto i: this->paths){
        printf("%d, ",i);
    }
    printf("\nNeighbors: ");
    for(auto i: this->neihbors){
        printf("%d, ",i);
    }
    printf("\n===================\n");

}

const vector<int> Room::takenDir() const{
    vector<int> spaces;
    spaces = this->paths;
    return spaces;
}

bool Room::hasNeighbor(int id){
    for(int i = 0; i < 8;i++){
        if(this->neihbors[i] == id){
            return true;
        }
    }
    return false;
}

//++++++++++++++
//PRIV-MODIFIERS
//--------------

//==============
//PRIV-ACCESSORS
//==============
