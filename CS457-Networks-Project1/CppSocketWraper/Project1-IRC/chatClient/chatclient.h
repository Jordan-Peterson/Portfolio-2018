#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <QMainWindow>
#include <QThread>
#include <QTextStream>
#include <QFile>
#include <QString>
#include <QList>
#include <QMap>
#include <QListWidgetItem>
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
    void on_sendButton_clicked();
    void handleResults(const QString& msg);

    void on_sendEdit_returnPressed();

    void on_channelList_itemClicked(QListWidgetItem *item);

private:
    Ui::ChatClient *ui;
    shared_ptr<clientSocket> mySocket;
    QString path;
    QMap<QString,QList<QString>> chatRooms;
    QString currRoom;

};

#endif // CHATCLIENT_H
