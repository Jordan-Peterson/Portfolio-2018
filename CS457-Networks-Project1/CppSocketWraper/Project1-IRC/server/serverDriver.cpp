#include <iostream>
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

int cclient(shared_ptr<client> usr,int id,commandHandler& handler)
{

    cout << "Waiting for message from Client Thread" << id << std::endl;
    string msg;
    ssize_t val =0;
    while (val != -1) 
    {
        tie(msg,val) = usr->getSock().get()->recvString();

        if(val != -1){
            handler.handleCommand(handler.splitMsg(msg),usr);
        }
    }
    cout << "disconnecting Thread: " << id << endl; 
    return 1; 
}


int main(int argc, char * argv[])
{
    cout << "Initializing Socket" << std::endl; 
    tcpServerSocket mysocket(2000);
    cout << "Binding Socket" << std::endl; 
    mysocket.bindSocket(); 
    cout << "Listening Socket" << std::endl; 
    mysocket.listenSocket(); 
    cout << "Waiting to Accept Socket" << std::endl;
    int id = 0; 
    vector<unique_ptr<thread>> threadList;
    shared_ptr<vector<shared_ptr<channel>>> chlist = make_shared<vector<shared_ptr<channel>>>();
    commandHandler handler(mysocket,chlist);
  
    while (ready)
    { 
        shared_ptr<tcpUserSocket> clientSocket;
        int val =0; 
        tie(clientSocket,val) = mysocket.acceptSocket();
        cout << "value for accept is " << val << std::endl; 
        cout << "Socket Accepted" << std::endl; 
        shared_ptr<client> c = make_shared<client>(clientSocket);
        unique_ptr<thread> t = make_unique<thread>(cclient,c,id,ref(handler)); 
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