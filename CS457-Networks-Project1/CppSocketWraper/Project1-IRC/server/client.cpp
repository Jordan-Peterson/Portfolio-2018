
#include "client.h"

client::client(shared_ptr<cs457::tcpUserSocket> sock):clientSocket(sock){};

void client::setNick(string nick){
    nickname = nick;
};

void client::setPass(string pass){
    password = pass;
};

