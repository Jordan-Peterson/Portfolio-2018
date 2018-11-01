#ifndef CHANNEL_H
#define CHANNEL_H

#include <string>
#include <vector>
#include "client.h"

using namespace std;

class channel{
    
    public:
        channel(string name);
        bool addClient(client);
        bool removeClient(client);
        inline string getChannelName(){return channelName;};
        inline vector<client> getClients(){return clients;};
        void sendAll(string msg);
        inline string getTopic(){return topic;};
        inline void setTopic(string tp){topic = tp;};

    private:
    string channelName;
    string topic;
    vector<client> clients;

};
#endif