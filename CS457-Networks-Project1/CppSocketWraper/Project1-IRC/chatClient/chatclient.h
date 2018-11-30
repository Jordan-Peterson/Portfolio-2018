#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <QMainWindow>
#include <QThread>
#include <QTextStream>
#include <QFile>
#include <QString>
#include <string.h>
#include "clientSocket.h"
#include "recthread.h"

namespace Ui {
class ChatClient;
}

class ChatClient : public QMainWindow
{
    Q_OBJECT
    WorkerThread* workerThread;
public:
    explicit ChatClient(QWidget *parent = 0, shared_ptr<clientSocket> sock =nullptr,QString p="");
    void startRecThread();
    ~ChatClient();

private slots:
    void on_pushButton_clicked();
    void handleResults(const QString& msg);

private:
    Ui::ChatClient *ui;
    shared_ptr<clientSocket> mySocket;
    QString path;
};

#endif // CHATCLIENT_H
