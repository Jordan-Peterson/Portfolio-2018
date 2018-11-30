#include "chatclient.h"
#include <QApplication>

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
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QFileInfo>
#include <QRegExp>
#include "clientSocket.h"

using namespace std;

QStringList conf;
QString ip;
int port;
QString logFile;
bool debug = false;
bool logIt = false;
time_t t= time(0);
QString path = "";



void initClient(){
    QString tmpPath = path;
    tmpPath.append(QString("/chatclient.conf"));
    QFile file(tmpPath);
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }

    QTextStream in(&file);

    while(!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(QRegExp("\\s+"));
        conf << fields;
    }


    for(int i = 0;i < conf.size();i++){
        if(conf.at(i) == "last_server_used"){
            ip = conf.at(i+1);
        }
        else if(conf.at(i) == "port"){
            port = (conf.at(i+1).toInt());
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

bool writeToFile(QString file, string newline){

    QFile fileOut(file);
    fileOut.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&fileOut);
    out << newline.c_str();

    // optional, as QFile destructor will already do it:
    fileOut.close();

    return true;

}

int main(int argc, char * argv[]){
    QFileInfo exec_fileinfo(argv[0]);
    path = exec_fileinfo.absolutePath();
    QApplication a(argc, argv);
    initClient();

    shared_ptr<clientSocket> socketptr = make_shared<clientSocket>(ip.toStdString(),port);
    socketptr->connectToServer();

    ChatClient w(0,socketptr,path);
    w.startRecThread();
    w.show();

    return a.exec();
}
