#pragma once

#include <sys/socket.h>
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <string.h> 
#include <memory> 
#include <vector>
#include <iostream>


//class forwards 
namespace cs457
{
    class clientSocket; 
    
}

namespace cs457
{
    using namespace std; 

    class clientSocket
    {
    public:
        clientSocket(uint portNumber);
        clientSocket(string networkAddress, uint portNumber);
        int connectToServer();
        int sendMessage(const string &data);
        int init();

    private: 
        uint port; 
        string address; 
        int serverSocket;

        struct sockaddr_in serverAddress; 
        struct sockaddr_in clientAddress;
        
    };


}

