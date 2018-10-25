#include <stdio.h>
#include <iostream>
#include "clientSocket.h"

using namespace std;

int main(int argc, char * argv[]){

    cs457::clientSocket mySocket(2000);
    mySocket.connectToServer();

    string input = "";

    while(input != "EXIT"){

        if(input != ""){
            mySocket.sendMessage(input);
        }

        cin >> input;
    }
    

    return 0;
};