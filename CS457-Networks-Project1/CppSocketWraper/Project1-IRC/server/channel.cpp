#include "channel.h"
#include <iterator>

channel::channel(string name):channelName(name){}

bool channel::addClient(client c){
    //lock_guard<mutex> lock(alter);
    //Check if the client is already in the list
    vector<client>::iterator clIter;
    for(clIter = clients.begin(); clIter != clients.end();advance(clIter,1)){
        if(*clIter == c){
            //if yes, do nothing and return
            return false;
        }
    }
    //if no, add client to the channel and return
    this -> clients.push_back(c);
    return true;
}

bool channel::removeClient(client c){
    
    //lock_guard<mutex> lock(alter);
    //Check if the client is in the channel
    vector<client>::iterator clIter;
    for(clIter = clients.begin(); clIter != clients.end();advance(clIter,1)){
        if(*clIter == c){
            //if yes, remove the client from the channel and return
            clients.erase(clIter);
            return true;
        }
    }
    //if no, do nothing and return
    return false;

}

void channel::sendAll(string msg){
    //lock_guard<mutex> lock(alter);

    vector<client>::iterator clIter;
    for(clIter = clients.begin(); clIter != clients.end();advance(clIter,1)){
        clIter -> getSock() -> sendString(msg);
    }
}
