#include "clientSocket.h"


cs457::clientSocket::clientSocket(uint portNumber):port(portNumber),address("127.0.0.1"){
    cs457::clientSocket::init();
};

cs457::clientSocket::clientSocket(string networkAddress, uint portNumber){
    cs457::clientSocket::init();

};

int cs457::clientSocket::init(){
    //clear the memory in the location of serverAddress
    memset(&serverAddress, '0', sizeof(serverAddress)); 
   
    //set serverAddress attributes and port
    serverAddress.sin_family = AF_INET; 
    serverAddress.sin_port = htons(port);

    return 0;
};

int cs457::clientSocket::connectToServer(){ //Got most of this function from geeksforgeeks.com: https://www.geeksforgeeks.org/socket-programming-cc/
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

int cs457::clientSocket::sendMessage(const string &data){
    if (data.size() == 0) return 0;                 
    int bufferSize = data.size()+1; 
    vector<char> stringBuffer(data.c_str(), data.c_str() + data.size() + 1u);

    ssize_t rval; 
    rval = send(serverSocket, &stringBuffer[0], bufferSize, 0);

    return rval;
}

