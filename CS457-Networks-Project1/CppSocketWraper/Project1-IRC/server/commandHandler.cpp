#include "commandHandler.h"

commandHandler::commandHandler(tcpServerSocket s):serverSocket(s){};

void commandHandler::handleCommand(vector<string> command,shared_ptr<client> usr){
    if(usr->getFirst()){
        if(commandMap.find(command[0]) == commandMap.end()){
            string s = "NOPE: you have to log-in/register to chat. type /PASS, /NICK, /USER.";
            thread thread(&tcpUserSocket::sendString,usr->getSock(),s,true);
            thread.join();
        }
        else{
            switch(commandMap.find(command[0])->second){
                
                case NICK:nickCommand(usr,command);usr->setNickSet(true);break;
                case PASS:passCommand(usr,command);usr->setPassSet(true);break;
                case QUIT:quitCommand(usr,command);break;
                default:string s = "NOPE: you have to log-in/register to chat. type /PASS, /NICK.";
                        thread thread(&tcpUserSocket::sendString,usr->getSock(),s,true);
                        thread.join();
            }
        }

        if(usr->getNickSet() && usr->getPassSet()){

            usr->setFirst(false);
            vector<string> clientInfo = checkUser(usr);
            if(clientInfo.size() != 0){
                cout << "found user" << endl;
                usr->setLevel(clientInfo.at(2));
                if(clientInfo.at(3) == "true"){
                    usr->setBanned(true);
                }
            }
            else{
                string line = usr->getNick() + " " + usr->getPass() + " " + usr->getLevel();
                if(usr->getBanned()){
                    line += " true"; 
                }
                else{
                    line += " false";
                }
                writeToFile("./db/users.txt","",line);
            }
        }

    }

    else if(commandMap.find(command[0]) == commandMap.end()){
        if(command[0][0] == '#' || command[0][0] == '&'){
            if(command.size() > 1){
                channel channel = *getChannel(command[0]);
                command.erase(command.begin());
                string message;
                for (auto const& s : command) { message += s; };
                vector<shared_ptr<client>> clients = channel.getClients();
                vector<shared_ptr<client>>::iterator clIter;
                for(clIter = clients.begin();clIter != clients.end();advance(clIter,1)){
                    string s = "[" + channel.getChannelName() + "] " + clIter->get()->getNick() + ": " + message;
                    thread t1(&tcpUserSocket::sendString,usr->getSock(),s,true);
                    t1.join();
                }
            }
        }
        else{
            thread t1(&tcpUserSocket::sendString,usr->getSock(),"invalid command: If you wish to talk in a channel, preface the sentance with the channel name starting with # or &",true);
            t1.join();
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
            case PASS:passCommand(usr,command);break;
            case PING:;
            case PONG:;
            case PRIVMSG:privmsgCommand(usr,command);break;
            case QUIT:quitCommand(usr,command);break;
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
    for(int i = 0;i < msg.size();i++){
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
    vector<shared_ptr<client>>::iterator clIter;
    for(clIter = clients.begin();clIter != clients.end();advance(clIter,1)){
        if(clIter->get()->getNick() == name){
            return *clIter;
        }
    }
    return NULL;
}

vector<shared_ptr<client>> commandHandler::getAllClients(){
    return clients;
}

void commandHandler::removeChannel(string channelName){
    
    channelList.erase(getChannel(channelName));
    writeToFile("./db/channels.txt",channelName,"");
        
}

bool commandHandler::checkChannel(string channelName){
    if(channelList.size() == 0){
        return false;
    }
    //Check if the name provided is an existing channel
    vector<channel>::iterator chIter;
    
    for(chIter = channelList.begin();chIter != channelList.end();advance(chIter,1)){
        if(chIter->getChannelName() == channelName){
            return true;
        }
    }
    return false;
}

vector<channel>::iterator commandHandler::getChannel(string channelName){
    vector<channel>::iterator chIter;
    for(chIter = channelList.begin();chIter != channelList.end();advance(chIter,1)){
        if(chIter->getChannelName() == channelName){
            return chIter;
        }
    }
    return chIter;
}

bool commandHandler::channelHasClient(string channelName,shared_ptr<client> cl){
    channel ch = *getChannel(channelName);
    vector<shared_ptr<client>> clients = ch.getClients();
    vector<shared_ptr<client>>::iterator clIter;

    for(clIter = clients.begin();clIter != clients.end();advance(clIter,1)){
        if(clIter->get()->getNick() == cl->getNick()){
            return true;
        }
    }
    return false;
}

vector<string> commandHandler::checkUser(shared_ptr<client> usr){
    clientList.clear();
    ifstream usersIn("./db/users.txt");
        string temp;
        getline(usersIn,temp);
        while (!usersIn.eof()) {
            istringstream buf(temp);
            istream_iterator<string> beg(buf), end;
            vector<string> line(beg,end);
            clientList.push_back(line);
            getline(usersIn,temp);
        }
    vector<vector<string>>::iterator usersIter;
    for(usersIter = clientList.begin();usersIter != clientList.end();advance(usersIter,1)){
        if(usersIter->at(0) == usr->getNick()){
            return *usersIter;
        }
    }
    return vector<string>();
}

bool commandHandler::writeToFile(string file, string check, string newline){

        ifstream openFile(file);
        ofstream newFile(file + ".new");
        string temp;
        getline(openFile,temp);
            while (!openFile.eof()) {
                istringstream buf(temp);
                istream_iterator<string> beg(buf), end;
                vector<string> line(beg,end);
                if(line[0] == check && check != ""){
                    newFile << newline << endl;
                }
                else{
                    newFile << temp << endl;
                }
                getline(openFile,temp);
            }

        if(check == ""){
            newFile << newline << endl;
        }
        openFile.close();
        newFile.close();
        string name = file + ".new";
        rename(name.c_str(),file.c_str());

    return true;

}

bool commandHandler::joinCommand(shared_ptr<client> usr, vector<string> msg){

    if(msg.size() >= 2){
        string channelName = msg[1];
        if(channelName[0] == '#' || channelName[0] == '&'){

            if(!checkChannel(channelName)){
                channel ch = channel(channel(channelName));
                channelList.push_back(ch);
                writeToFile("./db/channels.txt","",channelName);
            }
            if(!channelHasClient(channelName,usr)){
                (*getChannel(channelName)).addClient(usr);
                cout << "User " << usr->getNick() << " added to " << channelName << endl;
                thread t1(&tcpUserSocket::sendString,usr->getSock(),"You have been added to channel: " + channelName,true);
                t1.join();
                return true;
            }
            else{
                thread t1(&tcpUserSocket::sendString,usr->getSock(),"You are already in channel: " + channelName,true);
                t1.join();
                return false;
            }
        }
        else{
            thread t1(&tcpUserSocket::sendString,usr->getSock(),"Could not find/create channel, channel names begin with # or &",true);
            t1.join();
            return false;
        }
    }
    thread t1(&tcpUserSocket::sendString,usr->getSock(),"Invalid arguments for /JOIN",true);
    t1.join();
    return false;
}


bool commandHandler::partCommand(shared_ptr<client> usr, vector<string> msg){
    if(msg.size() >= 2){
        string channelName = msg[1];
        if(checkChannel(channelName) && channelHasClient(channelName,usr)){
            (*getChannel(channelName)).removeClient(usr);
            cout << "user " << usr->getNick() << " removed from " << channelName << endl;
            thread t1(&tcpUserSocket::sendString,usr->getSock(),"You have been removed from channel: " + channelName,true);
            t1.join();
        }
        if((*getChannel(channelName)).getClients().size() == 0){
            removeChannel(channelName);
            cout << "channel " + channelName + " has been deleted" <<endl;
        }
        return true;
    }
    return false;
}

bool commandHandler::infoCommand(shared_ptr<client> usr, vector<string> msg){
    thread t1(&tcpUserSocket::sendString,usr->getSock(),"Server Info: IP= " + serverSocket.getIP() + " Port= " + to_string(serverSocket.getPort()),true);
    t1.join();
    return true;
}

bool commandHandler::listCommand(shared_ptr<client> usr, vector<string> msg){
    string channels = "";
    vector<channel>::iterator chIter;
    for(chIter = channelList.begin();chIter != channelList.end();advance(chIter,1)){
        if(chIter == channelList.begin()){
            channels += chIter->getChannelName();
        }
        else{
            channels += ", " + chIter->getChannelName();
        }
    }
    thread t1(&tcpUserSocket::sendString,usr->getSock(),"List of all channels: " + channels,true);
    t1.join();
    return true;
}

bool commandHandler::nickCommand(shared_ptr<client> usr, vector<string> msg){
    if(msg.size() >= 2){
        string oldName = usr->getNick();
        usr->setNick(msg[1]);
        if(checkUser(usr).size() != 0){
            thread t1(&tcpUserSocket::sendString,usr->getSock(),"[Server]: Nickname taken, choose another please.",true);
            t1.join();
            usr->setNick(oldName);
            return false;
        }
        string ban;
        if(usr->getBanned()){
            ban = "true";
        }
        else{
            ban = "false";
        }
        writeToFile("./db/users.txt",oldName, usr->getNick() + " " + usr->getPass() + " " + usr->getLevel() + " " + ban);
        string response = "user nickname changed from: " + oldName + " to: " + usr->getNick();
        cout << response << endl;
        thread t1(&tcpUserSocket::sendString,usr->getSock(),response,true);
        t1.join();
        return true;
    }
    else{
        thread t1(&tcpUserSocket::sendString,usr->getSock(),"nickname not changed: possible invalid arguments to /NICK",true);
        t1.join();
        return false;
    }

}

bool commandHandler::topicCommand(shared_ptr<client> usr, vector<string> msg){
    string channelName = msg[1];
    //List the topic of the channel
    if(msg.size() == 2){
        thread t1(&tcpUserSocket::sendString,usr->getSock(),"channel " + channelName + " topic is: " + (*getChannel(channelName)).getTopic(),true);
        t1.join();
        return true;
    }
    //Change the topic of the channel
    else if(msg.size() >= 3){
        msg.erase(msg.begin());
        msg.erase(msg.begin());
        string newTopic = convertMsgtoString(msg);
        
        (*getChannel(channelName)).setTopic(newTopic);
        cout << "channel: " + msg[1] + " topic has been changed to: " + newTopic << endl;
        thread t1(&tcpUserSocket::sendString,usr->getSock(),"channel: " + channelName + " topic has been changed to: " + newTopic,true);
        t1.join();
        return true;

    }
    //Do nothing
    else{
        thread t1(&tcpUserSocket::sendString,usr->getSock(),"invalid arguments for /TOPIC",true);
        t1.join();
        return false;
    }
}

bool commandHandler::whoCommand(shared_ptr<client> usr, vector<string> msg){
    if(msg.size() < 2){
        vector<shared_ptr<client>> allClients = getAllClients();
        vector<shared_ptr<client>>::iterator clIter;
        for(clIter = allClients.begin();clIter != allClients.end();advance(clIter,1)){
            thread t1(&tcpUserSocket::sendString,usr->getSock(),clIter->get()->getNick(),true);
            t1.join();
        }
        return true;
    }
    else{
        regex e("(*)(" + msg[1] + ")(*)");
        vector<shared_ptr<client>> allClients = getAllClients();
        vector<shared_ptr<client>>::iterator clIter;
        for(clIter = allClients.begin();clIter != allClients.end();advance(clIter,1)){
            if(regex_match(clIter->get()->getNick().begin(),clIter->get()->getNick().end(),e)){
                thread t1(&tcpUserSocket::sendString,usr->getSock(),clIter->get()->getNick(),true);
                t1.join();
            }
        }
        return true;
    }
    return false;
}

bool commandHandler::privmsgCommand(shared_ptr<client> usr, vector<string> msg){
    
    string toClient = msg[1];
    string message = convertMsgtoString(msg);
    thread t1(&tcpUserSocket::sendString,usr->getSock(),"{" + usr->getNick() + "}" + message,true);
    t1.join();
    return true;
    
}

bool commandHandler::passCommand(shared_ptr<client> usr, vector<string> msg){
    if(msg.size() > 1){
        if(msg[1].find_first_of('@') != string::npos){
            thread t(&tcpUserSocket::sendString,usr->getSock(),"[Server]: password not set, no '@' symbols allowed!",true);
            t.join();
            return false;
        }
        usr->setPass(msg[1]);
        string ban;
        if(usr->getBanned()){
            ban = "true";
        }
        else{
            ban = "false";
        }
        writeToFile("./db/users.txt",usr->getNick(),usr->getNick() + " " + msg[1] + " " + usr->getLevel() + " " + ban);
        thread t1(&tcpUserSocket::sendString,usr->getSock(),"[Server]: password set",true);
        t1.join();
        return true;
    }
    else{
        thread t1(&tcpUserSocket::sendString,usr->getSock(),"invalid parameters: /PASS takes a no-space password",true);
        t1.join();
        return false;
    }
}

bool commandHandler::quitCommand(shared_ptr<client> usr, vector<string> msg){
    vector<channel>::iterator chIter = channelList.begin();
    for(;chIter != channelList.end();advance(chIter,1)){
        if(checkChannel(usr->getNick())){
            chIter->removeClient(usr);
        }
    }
    writeToFile("./db/users.txt",usr->getNick(),"");
    thread t(&tcpUserSocket::sendString,usr->getSock(),"You have left JPIRC, See you soon!",true);
    t.join();
    usr->getSock()->closeSocket();
    return true;
}