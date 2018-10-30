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

int cclient(client usr,int id,commandHandler handler)
{

    cout << "Waiting for message from Client Thread" << id << std::endl;
    string msg;
    ssize_t val;
    bool cont =true ;  
    while (cont) 
    {
        tie(msg,val) = usr.getSock().get()->recvString();
        
        handler.handleCommand(handler.splitMsg(msg),usr);

        if (msg.substr(0,4) == "EXIT")
            cont = false; 
       
        cout << "[SERVER] The client is sending message " << msg << " -- With value return = " << val << endl;
        string s =  "[SERVER REPLY] The client is sending message:" + msg  + "\n"; 
        thread childT1(&tcpUserSocket::sendString,usr.getSock().get(),s,true);
        //thread childT2(&cs457::tcpUserSocket::sendString,clientSocket.get(),msg,true);
        //thread childT3(&cs457::tcpUserSocket::sendString,clientSocket.get(),"\n",true);
        
        childT1.join();
        //childT2.join(); 
        //childT3.join(); 
        //clientSocket.get()->sendString(msg); 
        //clientSocket.get()->sendString("\n"); 
         if (msg.substr(0,6) == "SERVER")
        {
            thread childTExit(&tcpUserSocket::sendString,usr.getSock().get(),"GOODBYE EVERYONE",false);
            thread childTExit2(&tcpUserSocket::sendString,usr.getSock().get(),"\n",false);
            ready = false;   
            cont = false;   
            childTExit.join(); 
            childTExit2.join();
        }
        else
        {
            cout << "waiting for another message" << endl; 
        }
    }

    usr.getSock().get()->sendString("goodbye"); 
    
    usr.getSock().get()->closeSocket(); 
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
    vector<shared_ptr<channel>> channelList;
    shared_ptr<channel> ch1 = make_shared<channel>(channel("General"));
    shared_ptr<channel> ch2 = make_shared<channel>(channel("secret"));
    channelList.push_back(ch1);
    channelList.push_back(ch2);

    commandHandler handler(mysocket,channelList);
  
    while (ready)
    { 
        shared_ptr<tcpUserSocket> clientSocket;
        int val; 
        tie(clientSocket,val) = mysocket.acceptSocket();
        cout << "value for accept is " << val << std::endl; 
        cout << "Socket Accepted" << std::endl; 
        client c = client(clientSocket);
        channelList.at(0) ->addClient(c);
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