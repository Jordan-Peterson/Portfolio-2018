#include "commandHandler.h"

commandHandler::commandHandler(tcpServerSocket s):serverSocket(s){};

void commandHandler::handleCommand(vector<string> command,client usr){
    if(commandMap.find(command[0]) == commandMap.end()){
        
    }
    else{
        switch(commandMap.find(command[0])->second){
            case LIST:listCommand(usr,command);break;
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
            case NICK:nickCommand(usr,command);break;
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
            case TOPIC:topicCommand(usr, command);
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

void commandHandler::removeChannel(string channelName){
    vector<shared_ptr<channel>>::iterator chIter;
    for(chIter = channelList.begin();chIter != channelList.end();advance(chIter,1)){
        if(chIter->get()->getChannelName() == channelName){
            channelList.erase(chIter);
        }
    }
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
        if(!checkChannel(channelName)){
            shared_ptr<channel> ch = make_shared<channel>(channel(channelName));
            channelList.push_back(ch);
        }
        if(!channelHasClient(channelName,usr)){
            getChannel(channelName)->addClient(usr);
            cout << "User " << usr.getNick() << " added to " << channelName << endl;
            usr.getSock()->sendString("You have been added to channel: " + channelName);
            return true;
        }
        else{
            usr.getSock()->sendString("You are already in channel: " + channelName);
            return false;
        }
    }
    usr.getSock()->sendString("Invalid arguments for /JOIN");
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
        if(getChannel(channelName)->getClients().size() == 0){
            removeChannel(channelName);
            cout << "channel " + channelName + " has been deleted" <<endl;
        }
    }
    return false;
}

bool commandHandler::infoCommand(client usr, vector<string> msg){
    usr.getSock()->sendString("Server Info: IP= " + serverSocket.getIP() + " Port= " + to_string(serverSocket.getPort()));
    return true;
}

bool commandHandler::listCommand(client usr, vector<string> msg){
    string channels = "";
    vector<shared_ptr<channel>>::iterator chIter;
    for(chIter = channelList.begin();chIter != channelList.end();advance(chIter,1)){
        if(chIter == channelList.begin()){
            channels += chIter->get()->getChannelName();
        }
        else{
            channels += ", " + chIter->get()->getChannelName();
        }
    }
    usr.getSock()->sendString("List of all channels: " + channels);
    return true;
}

bool commandHandler::nickCommand(client usr, vector<string> msg){
    if(msg.size() >= 2){
        string oldName = usr.getNick();
        usr.setNick(msg[1]);
        string response = "user nickname changed from: " + oldName + " to: " + usr.getNick();
        cout << response << endl;
        usr.getSock()->sendString(response);
        return true;
    }
    else{
        usr.getSock()->sendString("nickname not changed: possible invalid arguments to /NICK");
        return false;
    }

}

bool commandHandler::topicCommand(client usr, vector<string> msg){
    //List the topic of the channel
    if(msg.size() == 2){
        usr.getSock()->sendString("channel " + msg[1] + " topic is: " + getChannel(msg[1])->getTopic());
        return true;
    }
    //Change the topic of the channel
    else if(msg.size() >= 3){
        string newTopic = "";
        for(int i = 2;i < msg.size();i++){
            if(i == msg.size()-1){
                newTopic += msg[i];
            }
            else{
                newTopic += msg[i] + " ";
            }
        }
        
        getChannel(msg[1])->setTopic(newTopic);
        cout << "channel: " + msg[1] + " topic has been changed to: " + newTopic << endl;
        usr.getSock()->sendString("channel: " + msg[1] + " topic has been changed to: " + newTopic);
        return true;

    }
    //Do nothing
    else{
        usr.getSock()->sendString("invalid arguments for /TOPIC");
        return false;
    }
}