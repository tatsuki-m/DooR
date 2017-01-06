#ifndef UNIX_DOMAIN_SOCKET_SERVER_H_
#define UNIX_DOMAIN_SOCKET_SERVER_H_

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
#include <vector>
#include <thread>

#include "door_worker.h"
#include "socket_ack.h"

class UnixDomainSocketServer
{

public:
    UnixDomainSocketServer();
    ~UnixDomainSocketServer();
    void run();

private:
    void create();
    void serve();
    void handle(int);
    void sendAck(int, SocketAck&);
    void createDoorWorker(std::string);
    bool getRequest(int, SocketAck&);
    void closeSocket();
    void deleteWorkers();
    int server_;
    std::string socketName_;
    std::vector<DoorWorker*> doorWorkers;

};
#endif

