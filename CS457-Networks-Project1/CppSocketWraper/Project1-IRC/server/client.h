

#include <string.h>
#include "tcpUserSocket.h"

using namespace std; 
class client{
    public:
        client(shared_ptr<cs457::tcpUserSocket> sock);
        void setNick(string nick);
        void setPass(string pass);
        inline string getNick(){return nickname;};
        inline string getPass(){return password;};
    
    private: 
        string nickname;
        string password;
        shared_ptr<cs457::tcpUserSocket> clientSocket;

};




