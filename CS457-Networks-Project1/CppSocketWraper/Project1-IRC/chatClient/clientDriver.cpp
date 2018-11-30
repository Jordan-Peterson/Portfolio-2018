#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <strings.h>
#include <vector>
#include <iterator>
#include <iostream>
#include <thread>
#include <ctime>
#include "clientSocket.h"

using namespace std;

vector<string> conf;
string ip;
int port;
string logFile;
bool debug = false;
bool logIt = false;
time_t t= time(0); 

int recClient(clientSocket& csocket){
    cout << "Start Chatting:" << std::endl;
    string msg = "";
    ssize_t val = -1;
    while (val != 0) 
    {
        tie(msg,val) = csocket.recvString();
        if(val !=0){
            vector<string> message;
            istringstream ss(msg);
            copy(istream_iterator<string>(ss) ,istream_iterator<string>() ,back_inserter(message));
            if(message[0] == "[PING]"){
                csocket.sendString("/PONG " + msg[2]);
            }
        }

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
            if(conf.at(i+1) == "True"){
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

bool writeToFile(string file, string newline){

        ifstream openFile(file);
        ofstream newFile(file + ".new");
        string temp;
        getline(openFile,temp);
            while (!openFile.eof()) {
                newFile << temp << endl;
                getline(openFile,temp);
            }
        newFile << newline << endl;
        
        openFile.close();
        newFile.close();
        string name = file + ".new";
        rename(name.c_str(),file.c_str());

    return true;

}

int main(int argc, char * argv[]){

    initClient();
    clientSocket mySocket("127.0.0.1",5000);
    mySocket.connectToServer();
    
    thread recThread(recClient, ref(mySocket)); 

    string input = "";
    
    while(input != "/QUIT"){

        getline(cin,input);
        
        if(input != ""){
            mySocket.sendString(input);
            if(logIt){
                
                string message = ctime(&t) + input;
                writeToFile(logFile,message);
            }
            
        }
    }

    recThread.join();

    cout << "Closing Client" << endl;

    return 0;
};
