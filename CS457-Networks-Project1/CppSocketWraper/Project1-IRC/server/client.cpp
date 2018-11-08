
#include "client.h"

client::client(shared_ptr<tcpUserSocket> sock):clientSocket(sock),nickname("Anonymous"),password(""){};


