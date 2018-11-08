#include "commandHandler.h"

commandHandler::commandHandler(tcpServerSocket s,shared_ptr<vector<shared_ptr<channel>>> chlist):serverSocket(s),channelList(chlist){};

void commandHandler::handleCommand(vector<string> command,shared_ptr<client> usr){
    if(commandMap.find(command[0]) == commandMap.end()){
        if(command[0][0] == '#' || command[0][0] == '&'){
            if(command.size() > 1){
                shared_ptr<channel> channel = *getChannel(command[0]);
                command.erase(command.begin());
                string message;
                for (auto const& s : command) { message += s; };
                vector<shared_ptr<client>> clients = channel->getClients();
                vector<shared_ptr<client>>::iterator clIter;
                for(clIter = clients.begin();clIter != clients.end();advance(clIter,1)){
                    clIter->get()->getSock()->sendString("[" + channel->getChannelName() + "] " + clIter->get()->getNick() + ": " + message);
                }
            }
        }
        else{
            usr->getSock()->sendString("invalid command: If you wish to talk in a channel, preface the sentance with the channel name starting with # or &");
        }
    }
    else{
        //lock this
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
            case PRIVMSG:privmsgCommand(usr,command);break;
            case QUIT:usr->getSock()->closeSocket();break;
            case RESTART:;
            case RULES:;
            case SETNAME:;
            case SILENCE:;
            case TIME:;
            case TOPIC:topicCommand(usr, command);break;
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

string commandHandler::convertMsgtoString(vector<string> msg){
    string message = "";
    msg.erase(msg.begin());
    for(int i = 2;i < msg.size();i++){
            if(i == msg.size()-1){
                 message += msg[i];
            }
            else{
                message += msg[i] + " ";
            }
        }   
    return message;
}

shared_ptr<client> commandHandler::getClient(string name){
    vector<shared_ptr<channel>>::iterator chIter;
    for(chIter = channelList->begin();chIter != channelList->end();advance(chIter,1)){
        vector<shared_ptr<client>>::iterator clIter = chIter->get()->getClients().begin();
        for(clIter;clIter != chIter->get()->getClients().end();advance(clIter,1)){
            if(clIter->get()->getNick() == name){
                return *clIter;
            }
        }
    }
    return NULL;
}

vector<shared_ptr<client>> commandHandler::getAllClients(){
    vector<shared_ptr<client>> allClients;
    vector<shared_ptr<channel>>::iterator chIter;
    for(chIter = channelList->begin();chIter != channelList->end();advance(chIter,1)){
        allClients.insert(allClients.end(),chIter->get()->getClients().begin(),chIter->get()->getClients().end());
    }
    sort( allClients.begin(), allClients.end());
    allClients.erase( unique( allClients.begin(), allClients.end() ), allClients.end() );
    return allClients;
}

void commandHandler::removeChannel(string channelName){
    
    channelList->erase(getChannel(channelName));
        
}

bool commandHandler::checkChannel(string channelName){
    if(channelList->size() == 0){
        return false;
    }
    //Check if the name provided is an existing channel
    vector<shared_ptr<channel>>::iterator chIter;
    
    for(chIter = channelList->begin();chIter != channelList->end();advance(chIter,1)){
        if(chIter->get()->getChannelName() == channelName){
            return true;
        }
    }
    return false;
}

vector<shared_ptr<channel>>::iterator commandHandler::getChannel(string channelName){
    vector<shared_ptr<channel>>::iterator chIter;
    cout << channelName << endl;
    for(chIter = channelList->begin();chIter != channelList->end();advance(chIter,1)){
        cout << chIter->get()->getChannelName() << endl;
        if(chIter->get()->getChannelName() == channelName){
            return chIter;
        }
    }
    cout << "here" << endl;
    return chIter;
}

bool commandHandler::channelHasClient(string channelName,shared_ptr<client> cl){
    shared_ptr<channel> ch = *getChannel(channelName);
    if(ch.get() == NULL){
        return false;
    }
    vector<shared_ptr<client>> clients = ch->getClients();
    vector<shared_ptr<client>>::iterator clIter;

    for(clIter = clients.begin();clIter != clients.end();advance(clIter,1)){
        if(clIter->get()->getNick() == cl->getNick()){
            return true;
        }
    }
    return false;
}

bool commandHandler::joinCommand(shared_ptr<client> usr, vector<string> msg){

    if(msg.size() >= 2){
        string channelName = msg[1];
        if(channelName[0] == '#' || channelName[0] == '&'){

            if(!checkChannel(channelName)){
                shared_ptr<channel> ch = make_shared<channel>(channel(channelName));
                channelList->push_back(ch);
            }
            if(!channelHasClient(channelName,usr)){
                (*getChannel(channelName))->addClient(usr);
                cout << "User " << usr->getNick() << " added to " << channelName << endl;
                usr->getSock()->sendString("You have been added to channel: " + channelName);
                return true;
            }
            else{
                usr->getSock()->sendString("You are already in channel: " + channelName);
                return false;
            }
        }
        else{
            usr->getSock()->sendString("Could not find/create channel, channel names begin with # or &"); 
            return false;
        }
    }
    usr->getSock()->sendString("Invalid arguments for /JOIN");
    return false;
}


bool commandHandler::partCommand(shared_ptr<client> usr, vector<string> msg){
    if(msg.size() >= 2){
        string channelName = msg[1];
        if(checkChannel(channelName) && channelHasClient(channelName,usr)){
            (*getChannel(channelName)) ->removeClient(usr);
            cout << "user " << usr->getNick() << " removed from " << channelName << endl;
            usr->getSock()->sendString("You have been removed from channel: " + channelName);
        }
        if((*getChannel(channelName))->getClients().size() == 0){
            removeChannel(channelName);
            cout << "channel " + channelName + " has been deleted" <<endl;
        }
        return true;
    }
    return false;
}

bool commandHandler::infoCommand(shared_ptr<client> usr, vector<string> msg){
    usr->getSock()->sendString("Server Info: IP= " + serverSocket.getIP() + " Port= " + to_string(serverSocket.getPort()));
    return true;
}

bool commandHandler::listCommand(shared_ptr<client> usr, vector<string> msg){
    string channels = "";
    vector<shared_ptr<channel>>::iterator chIter;
    for(chIter = channelList->begin();chIter != channelList->end();advance(chIter,1)){
        if(chIter == channelList->begin()){
            channels += chIter->get()->getChannelName();
        }
        else{
            channels += ", " + chIter->get()->getChannelName();
        }
    }
    usr->getSock()->sendString("List of all channels: " + channels);
    return true;
}

bool commandHandler::nickCommand(shared_ptr<client> usr, vector<string> msg){
    if(msg.size() >= 2){
        string oldName = usr->getNick();
        usr->setNick(msg[1]);
        string response = "user nickname changed from: " + oldName + " to: " + usr->getNick();
        cout << response << endl;
        usr->getSock()->sendString(response);
        return true;
    }
    else{
        usr->getSock()->sendString("nickname not changed: possible invalid arguments to /NICK");
        return false;
    }

}

bool commandHandler::topicCommand(shared_ptr<client> usr, vector<string> msg){
    //List the topic of the channel
    if(msg.size() == 2){
        usr->getSock()->sendString("channel " + msg[1] + " topic is: " + (*getChannel(msg[1]))->getTopic());
        return true;
    }
    //Change the topic of the channel
    else if(msg.size() >= 3){
        string newTopic = convertMsgtoString(msg);
        
        (*getChannel(msg[1]))->setTopic(newTopic);
        cout << "channel: " + msg[1] + " topic has been changed to: " + newTopic << endl;
        usr->getSock()->sendString("channel: " + msg[1] + " topic has been changed to: " + newTopic);
        return true;

    }
    //Do nothing
    else{
        usr->getSock()->sendString("invalid arguments for /TOPIC");
        return false;
    }
}

bool commandHandler::whoCommand(shared_ptr<client> usr, vector<string> msg){
    if(msg.size() < 2){
        vector<shared_ptr<client>> allClients = getAllClients();
        vector<shared_ptr<client>>::iterator clIter;
        for(clIter = allClients.begin();clIter != allClients.end();advance(clIter,1)){
            cout << clIter->get()->getNick() << endl;
            usr->getSock()->sendString(clIter->get()->getNick());
        }
        return true;
    }
    else{
        regex e("(*)(" + msg[1] + ")(*)");
        vector<shared_ptr<client>> allClients = getAllClients();
        vector<shared_ptr<client>>::iterator clIter;
        for(clIter = allClients.begin();clIter != allClients.end();advance(clIter,1)){
            if(regex_match(clIter->get()->getNick().begin(),clIter->get()->getNick().end(),e))
            usr->getSock()->sendString(clIter->get()->getNick());
        }
        return true;
    }
    return false;
}

bool commandHandler::privmsgCommand(shared_ptr<client> usr, vector<string> msg){
    
    string toClient = msg[1];
    msg.erase(msg.begin());
    string message = convertMsgtoString(msg);
    getClient(toClient)->getSock()->sendString("{" + usr->getNick() + "}" + message);
    return true;
    
}