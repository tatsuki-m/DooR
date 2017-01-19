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
#include <csignal>

#include "door_worker.h"
#include "door_api/door_socket.h"

class UnixDomainSocketServer
{

public:
    UnixDomainSocketServer();
    ~UnixDomainSocketServer();
    void run();
    static void deleteWorkers();

private:
    void create();
    void serve();
    void handle(int);
    void sendAck(int, DoorSocket&);
    bool createDoorWorker(DoorSocket&);
    bool getRequest(int, DoorSocket&);
    void closeSocket();
    int server_;
    std::string socketName_;
    static std::vector<DoorWorker*> doorWorkers;

};

#endif

