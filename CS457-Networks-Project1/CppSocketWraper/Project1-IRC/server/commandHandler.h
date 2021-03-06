#ifndef C_HANDLE
#define C_HANDLE

#include <stdio.h>
#include <string>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <iostream>
#include <vector>
#include <thread>
#include <regex>
#include <ctime>
#include "channel.h"
#include "client.h"
#include "tcpServerSocket.h"

using namespace std;
using std::string;
using std::unordered_map;
using std::vector;

class commandHandler{
    public:
        commandHandler(tcpServerSocket s);
        void handleCommand(vector<string> command,shared_ptr<client> usr);
        vector<string> splitMsg(string msg);
        string convertMsgtoString(vector<string> msg);
        bool writeToFile(string file, string check, string line);
        vector<channel>::iterator getChannel(string channelName);
        shared_ptr<client> getClient(string name);
        vector<shared_ptr<client>> getAllClients();
        inline vector<channel> getChannelList(){return channelList;};
        inline void addClient(shared_ptr<client> c){clients.push_back(c);};
        inline void setClientList(vector<vector<string>> users){clientList = users;};
        inline void setChannelList(vector<channel> ch){channelList = ch;};
        inline void setdbPath(string s){dbPath = s;};
        bool userHasPermission(string channelName, string username, char perm);
        
    private:
        bool checkChannel(string channelName);
        vector<string> checkUser(shared_ptr<client> usr);
        inline void removeChannel(string channelName);
        bool channelHasClient(string channelName, shared_ptr<client> cl);
        bool joinCommand(shared_ptr<client> usr, vector<string> msg);
        bool partCommand(shared_ptr<client> usr, vector<string> msg);
        bool infoCommand(shared_ptr<client> usr, vector<string> msg);
        bool listCommand(shared_ptr<client> usr, vector<string> msg);
        bool nickCommand(shared_ptr<client> usr, vector<string> msg);
        bool topicCommand(shared_ptr<client> usr, vector<string> msg);
        bool whoCommand(shared_ptr<client> usr, vector<string> msg);
        bool privmsgCommand(shared_ptr<client> usr, vector<string> msg);
        bool passCommand(shared_ptr<client> usr, vector<string> msg);
        bool quitCommand(shared_ptr<client> usr, vector<string> msg);
        bool timeCommand(shared_ptr<client> usr, vector<string> msg);
        bool awayCommand(shared_ptr<client> usr, vector<string> msg);
        bool pingCommand(shared_ptr<client> usr, vector<string> msg);
        bool pongCommand(shared_ptr<client> usr, vector<string> msg);
        bool isonCommand(shared_ptr<client> usr, vector<string> msg);
        bool modeCommand(shared_ptr<client> usr, vector<string> msg);
        bool inviteCommand(shared_ptr<client> usr, vector<string> msg);
        bool noticeCommand(shared_ptr<client> usr, vector<string> msg);
        bool versionCommand(shared_ptr<client> usr, vector<string> msg);
        bool setnameCommand(shared_ptr<client> usr, vector<string> msg);
        bool userIpCommand(shared_ptr<client> usr, vector<string> msg);
        bool rulesCommand(shared_ptr<client> usr, vector<string> msg);
        bool helpCommand(shared_ptr<client> usr, vector<string> msg);
        bool connectCommand(shared_ptr<client> usr, vector<string> msg);
        bool kickCommand(shared_ptr<client> usr, vector<string> msg);
        bool silenceCommand(shared_ptr<client> usr, vector<string> msg);
        bool operCommand(shared_ptr<client> usr, vector<string> msg);
        bool whoisCommand(shared_ptr<client> usr, vector<string> msg);
        bool killCommand(shared_ptr<client> usr, vector<string> msg);
        bool wallopsCommand(shared_ptr<client> usr, vector<string> msg);
        bool userCommand(shared_ptr<client> usr, vector<string> msg);

        enum mtype {NONE,LIST,AWAY,CONNECT,DIE,HELP,INFO,INVITE,ISON,JOIN,KICK,KILL,KNOCK,MODE,NICK,NOTICE,PART,OPER,PASS,PING,PONG,PRIVMSG,QUIT,RESTART,RULES,SETNAME,SILENCE,TIME,TOPIC,USER,USERHOST,USERIP,USERS,VERSION,WALLOPS,WHO,WHOIS};
        unordered_map<string, mtype>commandMap = {{"/LIST",LIST},{"/AWAY",AWAY},{"/CONNECT",CONNECT},{"/DIE",DIE},{"/HELP",HELP},{"/INFO",INFO},{"/INVITE",INVITE},{"/ISON",ISON},{"/JOIN",JOIN},{"/KICK",KICK},{"/KILL",KILL},{"/KNOCK",KNOCK},{"/LIST",LIST},{"/MODE",MODE},{"/NICK",NICK},{"/NOTICE",NOTICE},{"/PART",PART},{"/OPER",OPER},{"/PASS",PASS},{"/PING",PING},{"/PONG",PONG},{"/PRIVMSG",PRIVMSG},{"/QUIT",QUIT},{"/RESTART",RESTART},{"/RULES",RULES},{"/SETNAME",SETNAME},{"/SILENCE",SILENCE},{"/TIME",TIME},{"/TOPIC",TOPIC},{"/USER",USER},{"/USERHOST",USERHOST},{"/USERIP",USERIP},{"/USERS",USERS},{"/VERSION",VERSION},{"/WALLOPS",WALLOPS},{"/WHO",WHO},{"/WHOIS",WHOIS}};
        
        string dbPath;
        vector<channel> channelList;
        vector<shared_ptr<client>> clients;
        vector<vector<string>> clientList;
        tcpServerSocket serverSocket;
};
#endif