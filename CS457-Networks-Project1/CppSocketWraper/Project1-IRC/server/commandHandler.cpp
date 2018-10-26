#include "commandHandler.h"

commandHandler::commandHandler(cs457::tcpServerSocket s):serverSocket(s){};

void commandHandler::handleCommand(string command,shared_ptr<cs457::tcpUserSocket> usrSocket){
    if(commandMap.find(command) == commandMap.end()){
        cout << command << endl;
    }
    else{
        switch(commandMap.find(command)->second){
            case LIST:cout << "/LIST accepted" <<endl;break;
            case AWAY:;
            case CONNECT:;
            case DIE:;
            case HELP:;
            case INFO:;
            case INVITE:;
            case ISON:;
            case JOIN:;
            case KICK:;
            case MODE:;
            case NICK:;
            case NOTICE:;
            case PART:;
            case OPER:;
            case PASS:;
            case PING:;
            case PONG:;
            case PRIVMSG:;
            case QUIT:;
            case RESTART:;
            case RULES:;
            case SETNAME:;
            case SILENCE:;
            case TIME:;
            case TOPIC:;
            case USER:;
            case USERHOST:;
            case USERIP:;
            case USERS:;
            case VERSION:;
            case WALLOPS:;
            case WHO:;
            case WHOIS:;
            default:;
        }
    }
}