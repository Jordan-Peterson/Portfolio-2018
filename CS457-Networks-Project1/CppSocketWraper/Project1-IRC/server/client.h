#ifndef CLIENT_H
#define CLIENT_H

#include <string.h>
#include "tcpUserSocket.h"

using namespace std; 
class client{
    public:
        client(shared_ptr<tcpUserSocket> sock);
        inline bool operator==(client c){return (c.getSock() == clientSocket);};
        inline void setNick(string nick){nickname = nick;};
        inline void setPass(string pass){password = pass;};
        inline void setAwayReply(string away){autoreply = away;};
        inline void setBanned(bool b){banned = b;};
        inline void setLevel(string l){level = l;};
        inline void setFirst(bool f){first = f;};
        inline void setNickSet(bool n){nickset = n;};
        inline void setPassSet(bool p){passset = p;};
        inline void setFullName(string n){fullname = n;};
        void addPerms(string s);
        void removePerms(string s);
        inline string getFullName(){return fullname;};
        inline string getNick(){return nickname;};
        inline string getPass(){return password;};
        inline string getAwayReply(){return autoreply;};
        inline bool getBanned(){return banned;};
        inline string getLevel(){return level;};
        inline bool getFirst(){return first;};
        inline bool getNickSet(){return nickset;};
        inline bool getPassSet(){return passset;};
        inline shared_ptr<tcpUserSocket> getSock(){return clientSocket;};
        inline void setSock(shared_ptr<tcpUserSocket> s){clientSocket = s;};
        inline bool operator < (client b){if(nickname < b.getNick()){return true;}else{return false;}};
    
    private: 
        string fullname;
        string nickname;
        string password;
        string level;
        string autoreply;
        string mode;
        bool banned;

        bool first = true;
        bool nickset = false;
        bool passset = false;

        shared_ptr<tcpUserSocket> clientSocket;

};
#endif

