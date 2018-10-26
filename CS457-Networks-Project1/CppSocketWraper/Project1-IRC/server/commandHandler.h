#include <stdio.h>
#include <string>
#include <unordered_map>
#include <iostream>
#include <vector>
#include <thread>
#include "tcpServerSocket.h"

using namespace std;
using std::string;
using std::unordered_map;
using std::vector;

class commandHandler{
    public:
        commandHandler(cs457::tcpServerSocket s);
        void handleCommand(string command,shared_ptr<cs457::tcpUserSocket> usrSocket);
        
    private:

        enum mtype {NONE,LIST,AWAY,CONNECT,DIE,HELP,INFO,INVITE,ISON,JOIN,KICK,KILL,KNOCK,MODE,NICK,NOTICE,PART,OPER,PASS,PING,PONG,PRIVMSG,QUIT,RESTART,RULES,SETNAME,SILENCE,TIME,TOPIC,USER,USERHOST,USERIP,USERS,VERSION,WALLOPS,WHO,WHOIS};
        unordered_map<string, mtype>commandMap = {{"/LIST",LIST},{"/AWAY",AWAY},{"/CONNECT",CONNECT},{"/DIE",DIE},{"/HELP",HELP},{"/INFO",INFO},{"/INVITE",INVITE},{"/ISON",ISON},{"/JOIN",JOIN},{"/KICK",KICK},{"/KILL",KILL},{"/KNOCK",KNOCK},{"/LIST",LIST},{"/MODE",MODE},{"/NICK",NICK},{"/NOTICE",NOTICE},{"/PART",PART},{"/OPER",OPER},{"/PASS",PASS},{"/PING",PING},{"/PONG",PONG},{"/PRIVMSG",PRIVMSG},{"/QUIT",QUIT},{"/RESTART",RESTART},{"/RULES",RULES},{"/SETNAME",SETNAME},{"/SILENCE",SILENCE},{"/TIME",TIME},{"/TOPIC",TOPIC},{"/USER",USER},{"/USERHOST",USERHOST},{"/USERIP",USERIP},{"/USERS",USERS},{"/VERSION",VERSION},{"/WALLOPS",WALLOPS},{"/WHO",WHO},{"/WHOIS",WHOIS}};
        
        cs457::tcpServerSocket serverSocket;
};