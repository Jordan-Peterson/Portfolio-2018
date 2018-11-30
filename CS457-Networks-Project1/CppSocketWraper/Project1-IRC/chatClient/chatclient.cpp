#include "chatclient.h"
#include <ctime>
#include "ui_chatclient.h"

ChatClient::ChatClient(QWidget *parent, shared_ptr<clientSocket> sock,QString p) :
    QMainWindow(parent),mySocket(sock),path(p),
    ui(new Ui::ChatClient)
{
    ui->setupUi(this);
    ui->plainTextEdit->moveCursor(QTextCursor::End);
    path.append(QString("/chat.log"));
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

void ChatClient::on_pushButton_clicked()
{
    string msg = ui->lineEdit->text().toStdString();
    ui->lineEdit->clear();
    mySocket->sendString(msg);

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

    ui->plainTextEdit->insertPlainText(msg + "\n");

}

void ChatClient::startRecThread(){
    workerThread = new WorkerThread(this->mySocket);
        connect(workerThread, SIGNAL(resultReady(const QString&)), this, SLOT(handleResults(const QString&)));
        connect(workerThread, SIGNAL(finished()), workerThread, SLOT(deleteLater()));
        workerThread->start();
}
