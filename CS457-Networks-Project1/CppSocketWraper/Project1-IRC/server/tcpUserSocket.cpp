#include "tcpUserSocket.h"


using namespace std; 

tcpUserSocket::tcpUserSocket() {};

void tcpUserSocket::setSocket(int sckt)  
{ 
    userSocket=sckt;
};


socklen_t tcpUserSocket::getLenghtPointer()
{
    socklen_t len = sizeof(userAddress);  
    return len;
};

int tcpUserSocket::getSocket()
{
    return userSocket;
}; 

int tcpUserSocket::closeSocket()
{
    shutdown(userSocket, SHUT_RDWR);
    close(userSocket);
    return 0;
}; 

void tcpUserSocket::setUserInfoIPv4(string address, uint16_t port)
{
    clientAddressIPv4 = address;
    clientPortIPv4 = port; 
}; 

std::tuple<string,ssize_t> tcpUserSocket::recvString(int bufferSize, bool useMutex)
{
    char stringBuffer[bufferSize]; 
    memset(stringBuffer, 0, sizeof(stringBuffer));    //change made here. Zeros out buffer.

    ssize_t recvMsgSize;

    if (useMutex)
    {
        lock_guard<mutex> lock(recvMutex);
        recvMsgSize = recv(userSocket, stringBuffer, bufferSize, 0); 
    }    
    else
    {
        recvMsgSize = recv(userSocket, stringBuffer, bufferSize, 0); 
    }
    
    
   
    return make_tuple(string(stringBuffer),recvMsgSize);     
};
        

ssize_t tcpUserSocket::sendString(const string & data, bool useMutex)
{
    //https://stackoverflow.com/questions/7352099/stdstring-to-char
    if (data.size() == 0) return 0;                 
    int bufferSize = data.size()+1; 
    vector<char> stringBuffer(data.c_str(), data.c_str() + data.size() + 1u);

    ssize_t rval; 
    if (useMutex)
    {
       lock_guard<mutex> lock(sendMutex);
       rval = send(userSocket, &stringBuffer[0], bufferSize, 0);
    }
    else
    {
       rval = send(userSocket, &stringBuffer[0], bufferSize, 0);     
    }

    return rval;
}

string tcpUserSocket::getUniqueIdentifier()
{ 
    //this unique identifier is arbitrary 
    //and it may not be useful for chat program (see other classes)
    //it has not been tested to be unique but for now, we don't need it. 
     string identifier  = "[" + clientAddressIPv4 + "," + to_string(clientPortIPv4) + "]"; 
     return identifier; 
};

struct sockaddr * tcpUserSocket::getAddressPointer()
{
    return ((struct sockaddr *) &userAddress);
};