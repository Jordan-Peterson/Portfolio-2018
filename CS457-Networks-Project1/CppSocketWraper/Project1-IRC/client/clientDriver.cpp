#include <stdio.h>
#include <fstream>
#include <sstream>
#include <strings.h>
#include <vector>
#include <iterator>
#include <iostream>
#include <thread>
#include "clientSocket.h"

using namespace std;

vector<string> conf;
string ip;
int port;
string logFile;
bool debug = false;
bool logIt = false;

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

void initClient(){
    ifstream confIn("./chatclient.conf");
    copy(istream_iterator<string>(confIn), istream_iterator<string>(), back_inserter(conf));

    for(int i = 0;i < conf.size();i++){
        if(conf.at(i) == "last_server_used"){
            ip = conf.at(i+1);
        }
        else if(conf.at(i) == "port"){
            port = stoi(conf.at(i+1));
        }
        else if(conf.at(i) == "default_debug_mode"){
            if(conf.at(i+1) == "true"){
                debug = true;
            }
            else{
                debug = false;
            }
        }
        else if(conf.at(i) == "log"){
            if(conf.at(i+1) == "true"){
                logIt = true;
            }
            else{
                logIt = false;
            }
        }
        else if(conf.at(i) == "default_log_file" && logIt){
            logFile = conf.at(i+1);
        }
    }
    
}

int main(int argc, char * argv[]){

    initClient();
    cout << ip << endl;
    clientSocket mySocket(ip,port);
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