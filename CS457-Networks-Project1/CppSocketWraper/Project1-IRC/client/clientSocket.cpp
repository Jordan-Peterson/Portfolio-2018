#include "clientSocket.h"


clientSocket::clientSocket(uint portNumber):port(portNumber),address("127.0.0.1"){
    clientSocket::init();
};

clientSocket::clientSocket(string networkAddress, uint portNumber){
    clientSocket::init();

};

int clientSocket::init(){
    //clear the memory in the location of serverAddress
    memset(&serverAddress, '0', sizeof(serverAddress)); 
   
    //set serverAddress attributes and port
    serverAddress.sin_family = AF_INET; 
    serverAddress.sin_port = htons(port);

    return 0;
};

int clientSocket::connectToServer(){ //Got most of this function from geeksforgeeks.com: https://www.geeksforgeeks.org/socket-programming-cc/
    int sock = 0;
    
    //create a socket that will use the tcp protocol
    if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    }

    //
    if(inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
    if (connect(sock, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 

    serverSocket = sock;

    return 0;
};

tuple<string,ssize_t> clientSocket::recvString(int bufferSize, bool useMutex)
{
    char stringBuffer[bufferSize]; 
    memset(stringBuffer, 0, sizeof(stringBuffer));    //change made here. Zeros out buffer.

    ssize_t recvMsgSize;

    if (useMutex)
    {
        lock_guard<mutex> lock(recvMutex);
        recvMsgSize = recv(serverSocket, stringBuffer, bufferSize, 0); 
    }    
    else
    {
        recvMsgSize = recv(serverSocket, stringBuffer, bufferSize, 0); 
    }
    
    
   
    return make_tuple(string(stringBuffer),recvMsgSize);     
};
        

ssize_t clientSocket::sendString(const string & data)
{
    //https://stackoverflow.com/questions/7352099/stdstring-to-char
    if (data.size() == 0) return 0;                 
    int bufferSize = data.size()+1; 
    vector<char> stringBuffer(data.c_str(), data.c_str() + data.size() + 1u);

    ssize_t rval; 
    rval = send(serverSocket, &stringBuffer[0], bufferSize, 0);

    return rval;
};

void clientSocket::closeConnection(){
    shutdown(serverSocket, SHUT_RDWR);
    close(serverSocket);
    serverSocket = 0;
};

