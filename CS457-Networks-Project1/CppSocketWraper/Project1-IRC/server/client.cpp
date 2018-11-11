
#include "client.h"

client::client(shared_ptr<tcpUserSocket> sock):clientSocket(sock),nickname("Anonymous"),password("@"),level("user"),banned(false){};


void client::addPerms(string s){
    string::iterator sIter = s.begin();
    for(;sIter != s.end();advance(sIter,1)){
        if(mode.find_first_of(*sIter) == string::npos){
            mode += *sIter;
        }
    }

}

void client::removePerms(string s){
    string::iterator sIter = s.begin();
    for(;sIter != s.end();advance(sIter,1)){
        if(mode.find_first_of(*sIter) != string::npos){
            mode.erase(sIter);
        }
    }
}