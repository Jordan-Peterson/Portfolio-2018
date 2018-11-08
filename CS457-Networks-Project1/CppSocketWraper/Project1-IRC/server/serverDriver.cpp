#include <iostream>
#include <fstream>
#include <sstream>
#include <string> 
#include <tuple> 
#include <thread> 
#include <vector> 
#include <memory> 
#include <time.h>
#include "tcpUserSocket.h"
#include "tcpServerSocket.h"
#include "commandHandler.h"
#include "client.h"
#include "channel.h"

using namespace std;

bool ready = true; 
tcpServerSocket mysocket(0);
vector<unique_ptr<thread>> threadList;
shared_ptr<commandHandler> handler;

string banner;
vector<string> banusers;
vector<vector<string>> channels;
vector<string> conf;
vector<vector<string>> users;
vector<int> ports;
string dbPath;

int cclient(shared_ptr<client> usr,int id,shared_ptr<commandHandler> handler)
{
    thread thread(&tcpUserSocket::sendString,usr->getSock(),banner,true);
    thread.join();
    cout << "Waiting for message from Client Thread" << id << std::endl;
    string msg;
    ssize_t val =0;
    while (val != -1) 
    {
        tie(msg,val) = usr->getSock().get()->recvString();
        if(val != -1){
            handler->handleCommand(handler->splitMsg(msg),usr);
        }
    }
    cout << "disconnecting Thread: " << id << endl; 
    return 1; 
}

int initServer(){
    try{

        //Read in the conf file for the server
        cout << "loading in config file" << endl;

        ifstream confIn("chatserver.conf");
        copy(istream_iterator<string>(confIn), istream_iterator<string>(), back_inserter(conf));

        //populate dbpath
        dbPath = conf[3];

        //populate given ports
        ports.push_back(stoi(conf[1]));
        for(int i = 5; i < conf.size();i++){
            ports.push_back(stoi(conf[i]));
        }

        //Try to set main port, if fail, try secondary ports
        bool fail = true;
        int i = 0;
        while(fail){
            try{
                mysocket = tcpServerSocket("127.0.0.1",(ports[i]));
                fail = false;
            }catch(exception e){
                if(i == ports.size()){
                    cout << "EXCEPTION: no ports available" << endl;
                    return -1;
                }
                i++;
            }
        }

        //Read in banner.txt
        ifstream bannerIn(dbPath + "/banner.txt");
        string bannerTemp;
        getline(bannerIn,bannerTemp);
        while (!bannerIn.eof()) {
            banner += bannerTemp + "\n";
            getline(bannerIn,bannerTemp);
        }

        //Read in banusers.txt
        ifstream banusersIn(dbPath + "/banusers.txt");
        
        copy(istream_iterator<string>(banusersIn), istream_iterator<string>(), back_inserter(banusers));

        //Read in channels.txt
        ifstream channelsIn(dbPath + "/channels.txt");
        string temp;
        getline(channelsIn,temp);
        while (!channelsIn.eof()) {
            istringstream buf(temp);
            std::istream_iterator<string> beg(buf), end;
            vector<string> line(beg,end);
            channels.push_back(line);
            getline(channelsIn,temp);
        }

        //Read in users.txt
        ifstream usersIn(dbPath + "/users.txt");
        
        getline(usersIn,temp);
        while (!usersIn.eof()) {
            istringstream buf(temp);
            istream_iterator<string> beg(buf), end;
            vector<string> line(beg,end);
            users.push_back(line);
            getline(usersIn,temp);
        }

    }catch(exception e){
        cout << "error with server initiation, check db files" << endl;
        return -1;
    }

    handler = make_shared<commandHandler>(mysocket);
    vector<channel> channelList;
    for(int i = 0; i < channels.size();++i){
        channel ch = channel(channels.at(i).at(0));
        if(channels.at(i).at(channels.size()-1) != "@"){
            ch.setPassword(channels.at(i).at(channels.size()-1));
        }
        if(channels.at(i).size() > 3){
            string topic="";
            for(int k = 1;k < channels.at(i).size()-1;k++){
                if(k == channels.at(i).size()-2){
                    topic += channels.at(i).at(k);
                }
                else{
                    topic += channels.at(i).at(k) + " ";
                }
            }
            ch.setTopic(topic);  
        }
        else{
            ch.setTopic(channels.at(i).at(1));
        }
        channelList.push_back(ch);
    }
    handler->setChannelList(channelList);

    handler->setClientList(users);

    handler->setdbPath(dbPath);

    //Set up the socket to listen
    cout << "Binding Socket" << std::endl; 
    mysocket.bindSocket(); 
    cout << "Listening Socket" << std::endl; 
    mysocket.listenSocket(); 
    cout << "Waiting to Accept Socket" << std::endl;

    return 1;
}


int main(int argc, char * argv[])
{
    initServer();
    int id = 0; 
  
    while (ready)
    { 
        shared_ptr<tcpUserSocket> clientSocket;
        int val =0; 
        tie(clientSocket,val) = mysocket.acceptSocket();
        cout << "value for accept is " << val << std::endl; 
        cout << "Socket Accepted" << std::endl; 
        shared_ptr<client> c = make_shared<client>(clientSocket);
        handler->addClient(c);
        unique_ptr<thread> t = make_unique<thread>(cclient,c,id,handler); 
        threadList.push_back(std::move(t)); 
        
        id++; //not the best way to go about it. 
       // threadList.push_back(t); 
       
    
        
    }

    for (auto& t: threadList)
    {
        t.get()->join();
    }
    
        
    cout << "Server is shutting down after one client" << endl; 
    return 0; 
}