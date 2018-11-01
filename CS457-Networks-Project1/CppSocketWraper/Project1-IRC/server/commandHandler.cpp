#include "commandHandler.h"

commandHandler::commandHandler(tcpServerSocket s, vector<shared_ptr<channel>> chl):serverSocket(s),channelList(chl){};

void commandHandler::handleCommand(vector<string> command,client usr){
    if(commandMap.find(command[0]) == commandMap.end()){
        
    }
    else{
        switch(commandMap.find(command[0])->second){
            case LIST:cout << "/LIST accepted" <<endl;break;
            case AWAY:;
            case CONNECT:;
            case DIE:;
            case HELP:;
            case INFO:infoCommand(usr,command);break;
            case INVITE:;
            case ISON:;
            case JOIN:joinCommand(usr,command);break;
            case KICK:;
            case MODE:;
            case NICK:;
            case NOTICE:;
            case PART:partCommand(usr,command);break;
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

vector<string> commandHandler::splitMsg(string msg){
    vector<string> ret;
    stringstream stream(msg);
    string word;

    while(getline(stream,word,' ')){
        ret.push_back(word);
    }

    return ret;
}

bool commandHandler::checkChannel(string channelName){
    //Check if the name provided is an existing channel
    vector<shared_ptr<channel>>::iterator chIter;

    for(chIter = channelList.begin();chIter != channelList.end();advance(chIter,1)){
        if(chIter->get()->getChannelName() == channelName){
            return true;
        }
    }
    return false;
}

shared_ptr<channel> commandHandler::getChannel(string channelName){
    vector<shared_ptr<channel>>::iterator chIter;

    for(chIter = channelList.begin();chIter != channelList.end();advance(chIter,1)){
        if(chIter->get()->getChannelName() == channelName){
            return *chIter;
        }
    }
    return NULL;
}

bool commandHandler::channelHasClient(string channelName,client cl){
    shared_ptr<channel> ch = getChannel(channelName);
    if(ch.get() == NULL){
        return false;
    }
    vector<client> clients = ch->getClients();
    vector<client>::iterator clIter;

    for(clIter = clients.begin();clIter != clients.end();advance(clIter,1)){
        if(clIter->getNick() == cl.getNick()){
            return true;
        }
    }
    return false;
}

bool commandHandler::joinCommand(client usr, vector<string> msg){

    if(msg.size() >= 2){
        string channelName = msg[1];
        if(checkChannel(channelName) && !channelHasClient(channelName,usr)){
            getChannel(channelName)->addClient(usr);
            cout << "User " << usr.getNick() << " added to " << channelName << endl;
            usr.getSock()->sendString("You have been added to channel: " + channelName);
            return true;
        }
    }
    return false;
}


bool commandHandler::partCommand(client usr, vector<string> msg){
    if(msg.size() >= 2){
        string channelName = msg[1];
        if(checkChannel(channelName) && channelHasClient(channelName,usr)){
            getChannel(channelName) ->removeClient(usr);
            cout << "user " << usr.getNick() << " removed from " << channelName << endl;
            usr.getSock()->sendString("You have been removed from channel: " + channelName);
            return true;
        }
    }
    return false;
}

bool commandHandler::infoCommand(client usr, vector<string> msg){
    usr.getSock()->sendString("Server Info: IP= " + serverSocket.getIP() + " Port= " + to_string(serverSocket.getPort()));
    return true;
}

