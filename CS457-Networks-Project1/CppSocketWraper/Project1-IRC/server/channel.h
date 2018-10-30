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

    private:
    string channelName;
    vector<client> clients;

};
#endif