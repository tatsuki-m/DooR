#ifndef SHARED_DATA_SOCKET_SERVER_H_
#define SHARED_DATA_SOCKET_SERVER_H_

#include <iostream>
#include <errno.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <string>
#include <csignal>

//#include "door_unix_domain_socket_client/SockAck.h"

class SharedDataSocketServer
{
public:
    SharedDataSocketServer();
    ~SharedDataSocketServer();

private:
//    void create();
    //void serve();
    //void handle(int);
    //void closeSocket();
    //std::string socketName_;
};

#endif

