#include "chatclient.h"
#include "ui_chatclient.h"

ChatClient::ChatClient(QWidget *parent, shared_ptr<clientSocket> sock) :
    QMainWindow(parent),mySocket(sock),
    ui(new Ui::ChatClient)
{
    ui->setupUi(this);
    ui->plainTextEdit->moveCursor(QTextCursor::End);
}

ChatClient::~ChatClient()
{
    string msg("/QUIT");
    mySocket->sendString(msg);
    workerThread->quit();
    workerThread->wait();
    delete ui;
}

void ChatClient::on_pushButton_clicked()
{
    string msg = ui->lineEdit->text().toStdString();
    ui->lineEdit->clear();
    mySocket->sendString(msg);

}

void ChatClient::handleResults(const QString& msg){

    ui->plainTextEdit->moveCursor(QTextCursor::EndOfBlock);
    ui->plainTextEdit->insertPlainText(msg);

}

void ChatClient::startRecThread(){
    workerThread = new WorkerThread(this->mySocket);
        connect(workerThread, SIGNAL(resultReady(const QString&)), this, SLOT(handleResults(const QString&)));
        connect(workerThread, SIGNAL(finished()), workerThread, SLOT(deleteLater()));
        workerThread->start();
}
