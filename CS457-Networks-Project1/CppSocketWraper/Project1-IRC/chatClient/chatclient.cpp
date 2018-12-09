#include "chatclient.h"
#include <ctime>
#include "ui_chatclient.h"

ChatClient::ChatClient(QWidget *parent, shared_ptr<clientSocket> sock,QString p) :
    QMainWindow(parent),mySocket(sock),path(p),
    ui(new Ui::ChatClient)
{
    ui->setupUi(this);
    ui->chatText->moveCursor(QTextCursor::End);
    path.append(QString("/chat.log"));
    ui->channelList->insertItem(0,QString::fromStdString("Command Center"));
    ui->channelList->item(0)->setSelected(true);
    ui->hostLabel->setText(QString::fromStdString("Host Address: <b>" +mySocket->getHost()));
    chatRooms[QString::fromStdString("Command Center")].append("");
    currRoom = QString::fromStdString("Command Center");
}

ChatClient::~ChatClient()
{
    string msg("/QUIT");
    mySocket->sendString(msg);
    workerThread->quit();
    workerThread->wait();
    mySocket->closeConnection();
    delete ui;
}

void ChatClient::on_sendButton_clicked()
{
    string msg = ui->sendEdit->text().toStdString();
    ui->sendEdit->clear();
    if(currRoom.toStdString() != "Command Center" && msg[0] == '/'){
        ui->chatText->insertPlainText("!! Commands can be entered in the Command Center !!\n");
        ui->chatText->moveCursor(QTextCursor::End);
    }
    else{
        if(currRoom.toStdString() != "Command Center"){
            string header = currRoom.toStdString();
            header = header.substr(1,header.length()-2);
            header.append(" " + msg);
            msg = header;

        }
        mySocket->sendString(msg);
        QStringList message = QString::fromStdString(msg).split(QRegExp("\\s+"));

        if(message.size() > 0){
            if((message.at(0)).toStdString() == "/JOIN" && connected == true){
                QString channelName = "[" + message[1] + "]";
                chatRooms[channelName].append("");
                ui->channelList->addItem("[" + message[1] + "]");
                QList<QListWidgetItem*> rows = ui->channelList->findItems(channelName,0);
                on_channelList_itemClicked(rows.first());

            }
            if((message.at(0)).toStdString() == "/PART"){
                if(message.size() > 1){
                    QList<QListWidgetItem*> rows = ui->channelList->findItems("[" + message[1] + "]",0);
                    ui->channelList->takeItem(ui->channelList->row(rows.first()));
                    chatRooms.remove("[" + message[1] + "]");
                }
            }
            if((message.at(0)).toStdString() == "/NICK"){
                if(message.size() > 1){
                    ui->nicknameLabel->setText("NICKNAME: <b>" + message[1]);
                    nickSet = true;
                }
            }
            if((message.at(0)).toStdString() == "/PASS"){
                passSet = true;
            }

            if((message.at(0)).toStdString() == "/SETNAME"){
                message.removeAt(0);

                ui->fullnameLabel->setText("FULLNAME: <b>"+message.join(" "));
            }

            if((message.at(0)).toStdString() == "/USER"){
                if(message.size() > 2){
                    ui->nicknameLabel->setText("NICKNAME: <b>" + message[1]);
                    message.removeAt(0);
                    message.removeAt(0);
                    ui->fullnameLabel->setText("FULLNAME: <b>" + message.join(" "));
                }
            }
        }
    }

    time_t rawtime;
      struct tm * timeinfo;
      char buffer [80];

      time (&rawtime);
      timeinfo = localtime (&rawtime);

      strftime (buffer,80,"[%c]",timeinfo);
    QFile fileOut(path);
    fileOut.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append);
    QTextStream out(&fileOut);
    out << QString::fromStdString(string(buffer) + ": " + msg + "\n");
    fileOut.close();

}

void ChatClient::handleResults(const QString& msg){
       QStringList message = msg.split(QRegExp("\\s+"));

       if(message.size() > 0){
           QString room = message[0];
           QString sent = msg;
           if(message[0] == "[CONNECTED]:"){
               connected = true;
               ui->channelList->addItem(QString::fromStdString("[#general]"));
               ui->channelList->addItem(QString::fromStdString("[&random_talk]"));
               chatRooms[QString::fromStdString("[#general]")].append("");
               chatRooms[QString::fromStdString("[&random_talk]")].append("");
               mySocket->sendString("/JOIN #general");
               mySocket->sendString("/JOIN &random_talk");
           }
           if(message[0] == "[NOTICE]:"){
                ui->serverNoticeText->insertPlainText(msg + "\n");
                ui->serverNoticeText->moveCursor(QTextCursor::End);
           }
           else if(message[0] == "[KICK]:"){
               QList<QListWidgetItem*> rows = ui->channelList->findItems("[" + message[message.length()-1] + "]",0);
               ui->channelList->takeItem(ui->channelList->row(rows.first()));
               chatRooms.remove("[" + message[message.length()-1] + "]");
           }
           else if(chatRooms.contains(room)){
               message.removeAt(0);
               sent = message.join(" ");
               chatRooms[room].append(sent +"\n");
           }
           else{
               room = QString::fromStdString("Command Center");
               chatRooms[room].append(msg +"\n");
           }

           if(currRoom == room){
               ui->chatText->insertPlainText(sent + "\n");
               ui->chatText->moveCursor(QTextCursor::End);
           }
       }
}

void ChatClient::startRecThread(){
    workerThread = new WorkerThread(this->mySocket);
        connect(workerThread, SIGNAL(resultReady(const QString&)), this, SLOT(handleResults(const QString&)));
        connect(workerThread, SIGNAL(finished()), workerThread, SLOT(deleteLater()));
        workerThread->start();
}


void ChatClient::on_sendEdit_returnPressed()
{
    on_sendButton_clicked();
}

void ChatClient::on_channelList_itemClicked(QListWidgetItem *item)
{
    currRoom = item->text();
    item->setSelected(true);
    ui->chatText->clear();
    QList<QString> roomText = chatRooms[currRoom];
    QList<QString>::Iterator roomIter = roomText.begin();
    for(;roomIter != roomText.end();roomIter++){
        ui->chatText->insertPlainText(*roomIter);
    }

}
