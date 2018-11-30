#include "recthread.h"



void WorkerThread::run() {
    string msg = "";
    int val = -1;
    while(val != 0){
        std::tie(msg,val) = client->recvString();
        if(val !=0){
           QString m = QString::fromStdString(msg);
           QStringList message = m.split(QRegExp("\\s+"));
            if(message.at(0).toStdString() == "[PING]"){
                client->sendString("/PONG " + message.at(2).toStdString());
            }
        }

        emit resultReady(QString::fromStdString(msg));
    }
}
