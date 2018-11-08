#include <stdio.h>
#include <iostream>
#include <thread>
#include "clientSocket.h"

using namespace std;

int recClient(clientSocket& csocket){
    cout << "Start Chatting:" << std::endl;
    string msg = "";
    ssize_t val = -1;
    while (val != 0) 
    {
        tie(msg,val) = csocket.recvString();

        cout << msg << endl;
       
    }
    cout << "Thread returning" << endl;
    return 1; 
}

int main(int argc, char * argv[]){

    clientSocket mySocket(2000);
    mySocket.connectToServer();
    
    thread recThread(recClient, ref(mySocket)); 

    string input = "";
    
    while(input != "/QUIT"){

        getline(cin,input);
        
        if(input != ""){
            mySocket.sendString(input);
        }
    }

    recThread.join();

    cout << "Closing Client" << endl;

    return 0;
};