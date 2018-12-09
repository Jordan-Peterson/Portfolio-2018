#include "channel.h"
#include <iterator>

channel::channel(string name):channelName(name),topic("Default Topic"),password("@"){}

bool channel::addClient(shared_ptr<client> c){
    //lock_guard<mutex> lock(alter);
    //Check if the client is already in the list
    vector<shared_ptr<client>>::iterator clIter;
    for(clIter = clients.begin(); clIter != clients.end();advance(clIter,1)){
        if(*clIter == c){
            //if yes, do nothing and return
            return false;
        }
    }
    //if no, add client to the channel and return
    clients.push_back(c);
    return true;
}

bool channel::removeClient(shared_ptr<client> c){
    
    //lock_guard<mutex> lock(alter);
    //Check if the client is in the channel
    vector<shared_ptr<client>>::iterator clIter;
    for(clIter = clients.begin(); clIter != clients.end();advance(clIter,1)){
        if(*(clIter->get()) == *c){
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

    vector<shared_ptr<client>>::iterator clIter;
    for(clIter = clients.begin(); clIter != clients.end();advance(clIter,1)){
        clIter->get()->getSock()->sendString(msg);
    }
}

void channel::addPerms(string s){
    string::iterator sIter = s.begin();
    for(;sIter != s.end();advance(sIter,1)){
        if(mode.find_first_of(*sIter) == string::npos){
            mode += *sIter;
        }
    }

}

void channel::removePerms(string s){
    string::iterator sIter = s.begin();
    for(;sIter != s.end();advance(sIter,1)){
        if(mode.find_first_of(*sIter) != string::npos){
            mode.erase(sIter);
        }
    }
}

bool channel::checkPerms(string name, char perm){
    if(perm == 'o'){
        for(int i = 0; i < operators.size();i++){
            if(operators[i] == name){
                return true;
            }
        }
        return false;
    }
    return false;
}

void channel::removeOperator(string name){
    
    vector<string>::iterator it = operators.begin();
    for(; it != operators.end();it++){
        if(*it == name){
            operators.erase(it);
        }
    }
}