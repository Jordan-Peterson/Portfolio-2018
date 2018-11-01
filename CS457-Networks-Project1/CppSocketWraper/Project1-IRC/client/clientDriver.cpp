#include <stdio.h>
#include <iostream>
#include <thread>
#include "clientSocket.h"

using namespace std;

int recClient(clientSocket& csocket){
    cout << "Waiting for message from Server " << std::endl;
    string msg;
    ssize_t val;
    bool cont =true ; 
    while (cont) 
    {
        tie(msg,val) = csocket.recvString();

        cout << msg << endl;
       
    }
    return 1; 
}

int main(int argc, char * argv[]){

    clientSocket mySocket(2000);
    mySocket.connectToServer();
    
    thread recThread(recClient, ref(mySocket)); 

    string input = "";

    while(input != "EXIT"){

        getline(cin,input);
        
        if(input != ""){
            mySocket.sendString(input);
        }

    }
    
    recThread.join();

    cout << "Closing Client" << endl;

    return 0;
};