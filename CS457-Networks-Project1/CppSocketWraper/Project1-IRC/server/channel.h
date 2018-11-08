#ifndef CHANNEL_H
#define CHANNEL_H

#include <string>
#include <vector>
#include "client.h"

using namespace std;

class channel{
    
    public:
        channel(string name);
        bool addClient(shared_ptr<client>);
        bool removeClient(shared_ptr<client>);
        inline void setChannelName(string s){channelName = s;};
        inline void setPassword(string s){password = s;};
        inline string getChannelName(){return channelName;};
        inline vector<shared_ptr<client>> getClients(){return clients;};
        void sendAll(string msg);
        inline string getTopic(){return topic;};
        inline void setTopic(string tp){topic = tp;};

    private:
        string channelName;
        string password;
        string topic;
        vector<shared_ptr<client>> clients;

};
#endif