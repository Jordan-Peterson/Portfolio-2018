#ifndef RECTHREAD_H
#define RECTHREAD_H

#include <QString>
#include <QObject>
#include <QThread>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include "clientSocket.h"

class WorkerThread : public QThread
{
    Q_OBJECT
public:
    WorkerThread(shared_ptr<clientSocket> c):client(c){}
public slots:
    void run();

signals:
    void resultReady(const QString &s);
private:
    shared_ptr<clientSocket> client;
};


#endif // RECTHREAD_H

