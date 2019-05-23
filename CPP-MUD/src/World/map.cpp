#include "../../include/World/map.h"

//=========
//CONSTRUCT
//=========
Map::Map(int id, int size){
    this->mapID = id;
    this->size = size;
    this->xDim = 0;
    this->yDim = 0;
    this->numHostile = 0;
    this->numPeaceful = 0;
}

Map::~Map(){

}

//+++++++++
//MODIFIERS
//---------
void Map::generateMap(const int size){
    //populate list of rooms based on size given
    //-start with one room
    int roomID = 1;
    rooms.push_back(make_shared<Room>(Room(roomID,0,0,"")));

    for(int i = 0; i < size; i++){
        //pick a random non-full room
        int r = rand() % rooms.size();
        shared_ptr<Room> randRoom = rooms.at(r);
        while (randRoom->takenDir().size() == 8){
            r = rand() % rooms.size();
            randRoom = rooms.at(r);
        }
        //look to an open direction
        vector<int> taken = randRoom->takenDir();
        vector<int> possible {0,1,2,3,4,5,6,7};
        vector<int> available;

        //take the set difference between taken and possible to get available paths for the given room
        std::set_difference(possible.begin(),possible.end(),taken.begin(),taken.end(),std::inserter(available,available.begin()));

        //choose random new path and update roooms
        int newPath = available.at(rand()%available.size());

        //check to see if that room already exists,
        // if it does, add the path and update both rooms,
        // else create a new room and do the same.

        int newX =0;
        int newY =0;
        //create new room and create connections
        switch(newPath){
            //north
            case 0: newX = randRoom->getX()-1;newY = randRoom->getY()+1;break;
            //east
            case 1: newX = randRoom->getX();newY = randRoom->getY()+1;break;
            //south
            case 2: newX = randRoom->getX()+1;newY = randRoom->getY()+1;break;
            //west
            case 3: newX = randRoom->getX()-1;newY = randRoom->getY();break;
            //northwest
            case 4: newX = randRoom->getX()+1;newY = randRoom->getY();break;
            //northeast
            case 5: newX = randRoom->getX()-1;newY = randRoom->getY()-1;break;
            //southeast
            case 6: newX = randRoom->getX();newY = randRoom->getY()-1;break;
            //southwest
            case 7: newX = randRoom->getX()+1;newY = randRoom->getY()-1;break;
            default: cout << "default" << endl;break;
        }

        //room does not already exist
        if(getRoomIndex(newX,newY) == -1){
            roomID++;
            this->rooms.push_back(make_shared<Room>(Room(roomID,newX,newY,"")));
            randRoom->addNeighbor(newPath,roomID);
            randRoom->addPath(newPath);
            this->rooms.at(getRoomIndex(roomID))->addNeighbor(7-newPath,randRoom->getID());
            this->rooms.at(getRoomIndex(roomID))->addPath((7-newPath));
        }
        else{
            i--;
        }

    }
}

int Map::getRoomIndex(int id){
    for(size_t i = 0; i < rooms.size();i++){
        if(this->rooms.at((int)i)->getID() == id){
            return i;
        }
    }
    return -1;

}

int Map::getRoomIndex(int x, int y){
    for(size_t i = 0; i < rooms.size();i++){
        if(this->rooms.at((int)i)->getX() == x && rooms.at((int)i)->getY() == y){
            return i;
        }
    }
    return -1;

}

//=========
//ACCESSORS
//=========
void Map::showMap() {
    //print out each room on the map
    vector<shared_ptr<Room>>::iterator roomiter = rooms.begin();
    for(;roomiter != rooms.end();roomiter++){
            roomiter->get()->showRoom();

    }
}

bool Map::roomTaken(int x, int y){
    vector<shared_ptr<Room>>::iterator roomiter = rooms.begin();
    for(;roomiter != rooms.end();roomiter++){
        if(roomiter->get()->getX() == x && roomiter->get()->getY() == y){
            return true;
        }
    }
    return false;
}

vector<shared_ptr<Room>>::iterator Map::getRoom(int x, int y){
    vector<shared_ptr<Room>>::iterator roomiter = rooms.begin();
    for(;roomiter != rooms.end();roomiter++){
        if(roomiter->get()->getX() == x && roomiter->get()->getY() == y){
            return roomiter;
        }
    }
    return roomiter;
}

//++++++++++++++
//PRIV-MODIFIERS
//--------------

//==============
//PRIV-ACCESSORS
//==============
