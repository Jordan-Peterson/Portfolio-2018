
#include "client.h"

client::client(shared_ptr<tcpUserSocket> sock):clientSocket(sock),nickname("Anonymous"),password(""){};

void client::setNick(string nick){
    nickname = nick;
};

void client::setPass(string pass){
    password = pass;
};

void client::setAwayReply(string away){
    autoreply = away;
}

