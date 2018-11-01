#ifndef C_HANDLE
#define C_HANDLE

#include <stdio.h>
#include <string>
#include <sstream>
#include <unordered_map>
#include <iostream>
#include <vector>
#include <thread>
#include "channel.h"
#include "client.h"
#include "tcpServerSocket.h"

using namespace std;
using std::string;
using std::unordered_map;
using std::vector;

class commandHandler{
    public:
        commandHandler(tcpServerSocket s, vector<shared_ptr<channel>> chl);
        void handleCommand(vector<string> command,client usr);
        vector<string> splitMsg(string msg);
        shared_ptr<channel> getChannel(string channelName);
        
    private:
        bool checkChannel(string channelName);
        bool channelHasClient(string channelName, client cl);
        bool joinCommand(client usr, vector<string> msg);
        bool partCommand(client usr, vector<string> msg);
        bool infoCommand(client usr, vector<string> msg);
        bool listCommand(client usr, vector<string> msg);
        bool nickCommand(client usr, vector<string> msg);
        bool topicCommand(client usr, vector<string> msg);

        enum mtype {NONE,LIST,AWAY,CONNECT,DIE,HELP,INFO,INVITE,ISON,JOIN,KICK,KILL,KNOCK,MODE,NICK,NOTICE,PART,OPER,PASS,PING,PONG,PRIVMSG,QUIT,RESTART,RULES,SETNAME,SILENCE,TIME,TOPIC,USER,USERHOST,USERIP,USERS,VERSION,WALLOPS,WHO,WHOIS};
        unordered_map<string, mtype>commandMap = {{"/LIST",LIST},{"/AWAY",AWAY},{"/CONNECT",CONNECT},{"/DIE",DIE},{"/HELP",HELP},{"/INFO",INFO},{"/INVITE",INVITE},{"/ISON",ISON},{"/JOIN",JOIN},{"/KICK",KICK},{"/KILL",KILL},{"/KNOCK",KNOCK},{"/LIST",LIST},{"/MODE",MODE},{"/NICK",NICK},{"/NOTICE",NOTICE},{"/PART",PART},{"/OPER",OPER},{"/PASS",PASS},{"/PING",PING},{"/PONG",PONG},{"/PRIVMSG",PRIVMSG},{"/QUIT",QUIT},{"/RESTART",RESTART},{"/RULES",RULES},{"/SETNAME",SETNAME},{"/SILENCE",SILENCE},{"/TIME",TIME},{"/TOPIC",TOPIC},{"/USER",USER},{"/USERHOST",USERHOST},{"/USERIP",USERIP},{"/USERS",USERS},{"/VERSION",VERSION},{"/WALLOPS",WALLOPS},{"/WHO",WHO},{"/WHOIS",WHOIS}};
        
        vector<shared_ptr<channel>> channelList;
        tcpServerSocket serverSocket;
};
#endif