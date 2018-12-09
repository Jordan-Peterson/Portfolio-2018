#ifndef Client_Socket
#define Client_Socket

#include <sys/socket.h>
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <unistd.h>
#include <string> 
#include <strings.h>
#include <memory>
#include <vector>
#include <iostream>
#include <mutex>
#include <tuple>
#include <cstring>



using namespace std; 


class clientSocket
{
public:
    clientSocket(const clientSocket&);
    clientSocket(uint portNumber);
    clientSocket(string networkAddress, uint portNumber);
    inline string getHost(){return address;}
    int connectToServer();
    void closeConnection();
    tuple<string,ssize_t> recvString(int bufferSize=4096,bool useMutex = true);
    ssize_t sendString(const string & data);
    int init();

private: 
    uint port; 
    string address; 
    int serverSocket;
    
    mutex recvMutex; 
    mutex sendMutex;

    struct sockaddr_in serverAddress; 
    struct sockaddr_in clientAddress;
    
};

#endif


