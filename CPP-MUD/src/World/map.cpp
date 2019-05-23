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
    rooms.push_back(Room(1,0,0,"",false,false,false,false,false,false,false,false));

    for(int i = 0; i < size; i++){
        //pick a random non-full room
        int r = rand() % rooms.size();
        Room& available = rooms.at(r);
        while (available.availableDir().size() < 1){
            r = rand() % rooms.size();
            available = rooms.at(r);
        }
        available.showRoom();
        //look to an open direction
        vector<int> choices = available.availableDir();
        vector<int>::iterator chiter = choices.begin();
        cout << "choices for: (" << available.getX() << "," << available.getY() << ") ";
        for(;chiter != choices.end();chiter++){
            cout << to_string(*chiter);
        }
        cout << endl;
        int selection = choices.at(rand() % choices.size());
        //create new room and create connections
        switch(choices.at(selection)){
            //north
            case 0: rooms.push_back(Room(available.getID()+1,available.getX(),available.getY()+1,"",false,false,false,false,false,true,false,false));available.setNorth(true);break;
            //east
            case 1: rooms.push_back(Room(available.getID()+1,available.getX()+1,available.getY(),"",false,false,false,false,true,false,false,false));available.setEast(true);break;
            //south
            case 2: rooms.push_back(Room(available.getID()+1,available.getX(),available.getY()-1,"",true,false,false,false,false,false,false,false));available.setSouth(true);break;
            //west
            case 3: rooms.push_back(Room(available.getID()+1,available.getX()-1,available.getY(),"",false,false,false,true,false,false,false,false));available.setWest(true);break;
            //northwest
            case 4: rooms.push_back(Room(available.getID()+1,available.getX()-1,available.getY()+1,"",false,false,false,false,false,false,true,false));available.setNorthWest(true);break;
            //northeast
            case 5: rooms.push_back(Room(available.getID()+1,available.getX()+1,available.getY()+1,"",false,false,false,false,false,false,false,true));available.setNorthEast(true);break;
            //southeast
            case 6: rooms.push_back(Room(available.getID()+1,available.getX()+1,available.getY()-1,"",false,false,true,false,false,false,false,false));available.setSouthEast(true);break;
            //southwest
            case 7: rooms.push_back(Room(available.getID()+1,available.getX()-1,available.getY()-1,"",false,true,false,false,false,false,false,false));available.setSouthWest(true);break;
            default: cout << "default" << endl;break;
        }


        // //go through all spaces and make random connections if it can
        // int peekX = (rooms.end()-1)->getX();
        // int peekY = (rooms.end()-1)->getY();

        // //north
        // if(roomTaken(peekX,peekY+1)){
        //     if(rand()%10 > 6){
        //         getRoom(peekX,peekY+1)->setNorth(true);
        //         (rooms.end()-1)->setNorth(true);
        //     }
        // }
        // //northeast
        // if(roomTaken(peekX+1,peekY+1)){
        //     if(rand()%10 > 6){
        //         getRoom(peekX+1,peekY+1)->setNorthEast(true);
        //         (rooms.end()-1)->setNorthEast(true);
        //     }
        // }
        // //northwest
        // if(roomTaken(peekX-1,peekY+1)){
        //     if(rand()%10 > 6){
        //         getRoom(peekX-1,peekY+1)->setNorthWest(true);
        //         (rooms.end()-1)->setNorthWest(true);
        //     }
        // }
        // //east
        // if(roomTaken(peekX-1,peekY)){
        //     if(rand()%10 > 6){
        //         getRoom(peekX-1,peekY)->setEast(true);
        //         (rooms.end()-1)->setEast(true);
        //     }
        // }
        // //west
        // if(roomTaken(peekX+1,peekY)){
        //     if(rand()%10 > 6){
        //         getRoom(peekX+1,peekY)->setWest(true);
        //         (rooms.end()-1)->setWest(true);
        //     }
        // }
        // //south
        // if(roomTaken(peekX,peekY-1)){
        //     if(rand()%10 > 6){
        //         getRoom(peekX,peekY-1)->setSouth(true);
        //         (rooms.end()-1)->setSouth(true);
        //     }
        // }
        // //southeast
        // if(roomTaken(peekX+1,peekY-1)){
        //     if(rand()%10 > 6){
        //         getRoom(peekX+1,peekY-1)->setSouthEast(true);
        //         (rooms.end()-1)->setSouthEast(true);
        //     }
        // }
        // //southwest
        // if(roomTaken(peekX-1,peekY-1)){
        //     if(rand()%10 > 6){
        //         getRoom(peekX-1,peekY-1)->setSouthWest(true);
        //         (rooms.end()-1)->setSouthWest(true);
        //     }
        // }
        showMap();
        cout << "from: " << available.getX() << "," << available.getY() << " to dir: " <<to_string(choices.at(selection)) << endl;
        cout << endl;
    }

}

//=========
//ACCESSORS
//=========
void Map::showMap() {
    //print out each room on the map
    vector<Room>::iterator roomiter = rooms.begin();
    for(;roomiter != rooms.end();roomiter++){
            cout << "RoomID: " << roomiter->getID() << " Coords: ("<< roomiter->getX() << "," << roomiter->getY() << ")" << endl;

    }
}

bool Map::roomTaken(int x, int y){
    vector<Room>::iterator roomiter = rooms.begin();
    for(;roomiter != rooms.end();roomiter++){
        if(roomiter->getX() == x && roomiter->getY() == y){
            return true;
        }
    }
    return false;
}

vector<Room>::iterator Map::getRoom(int x, int y){
    vector<Room>::iterator roomiter = rooms.begin();
    for(;roomiter != rooms.end();roomiter++){
        if(roomiter->getX() == x && roomiter->getY() == y){
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
