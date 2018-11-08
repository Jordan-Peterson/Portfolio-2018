#ifndef CLIENT_H
#define CLIENT_H

#include <string.h>
#include "tcpUserSocket.h"

using namespace std; 
class client{
    public:
        client(shared_ptr<tcpUserSocket> sock);
        inline bool operator==(client c){return (c.getSock() == clientSocket);};
        void setNick(string nick);
        void setPass(string pass);
        void setAwayReply(string away);
        inline string getNick(){return nickname;};
        inline string getPass(){return password;};
        inline string getAwayReply(){return autoreply;};
        inline shared_ptr<tcpUserSocket> getSock(){return clientSocket;};
        inline bool operator < (client b){if(nickname < b.getNick()){return true;}else{return false;}};
    
    private: 
        string nickname;
        string password;
        string autoreply;
        shared_ptr<tcpUserSocket> clientSocket;

};
#endif

