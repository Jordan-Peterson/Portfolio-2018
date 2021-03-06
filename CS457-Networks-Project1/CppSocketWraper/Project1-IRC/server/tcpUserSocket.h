#ifndef USER_SOCK
#define USER_SOCK

#include <sys/socket.h>
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <strings.h>
#include <string> 
#include <cstring>
#include <tuple> 
#include <unistd.h>
#include <assert.h>
#include <vector> 
#include <memory> 
#include <mutex>
#include <iostream>


using namespace std; 

class tcpUserSocket
{
    public:
        tcpUserSocket();
        void setSocket(int skct); 
        struct sockaddr * getAddressPointer();
        socklen_t getLenghtPointer();
        int getSocket(); 
        int closeSocket(); 
        std::tuple<string,ssize_t> recvString(int bufferSize=4096,bool useMutex = true);
        void setUserInfoIPv4(string clientAddress,uint16_t port);
        inline string getIP(){return clientAddressIPv4;};

        ssize_t sendString(const string & data,bool useMutex = true);
        string getUniqueIdentifier();
        

    private:
        struct sockaddr_in userAddress; 
        int userSocket; 
        string clientAddressIPv4; 
        uint16_t clientPortIPv4;
        mutex sendMutex;
        mutex recvMutex; 
};
#endif