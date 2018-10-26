#include <stdio.h>
#include <iostream>
#include "clientSocket.h"

using namespace std;

int main(int argc, char * argv[]){

    clientSocket mySocket(2000);
    mySocket.connectToServer();

    string input = "";

    while(input != "EXIT"){

        if(input != ""){
            mySocket.sendString(input);
        }

        cin >> input;
    }
    

    return 0;
};