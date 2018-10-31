#ifndef SERVER_SOCK
#define SERVER_SOCK

#include <sys/socket.h>
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <strings.h>
#include <string> 
#include <tuple> 
#include <unistd.h>
#include <memory> 
#include "tcpUserSocket.h"


 using namespace std; 
    class tcpServerSocket
    {
    public:
        tcpServerSocket(uint portNumber); 
        tcpServerSocket(string networkAddress, uint portNumber);
        int bindSocket();
        int listenSocket();
        tuple<shared_ptr<tcpUserSocket>,int> acceptSocket();
      
    private: 
        void init();
        void setSocketOptions();
        uint port; 
        string address; 
        
     
        //
        int serverSocket;
        
        struct sockaddr_in serverAddress; 
        struct in_addr addr;
        
    };
#endif