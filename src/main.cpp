#include <iostream>
#include <string>
#include <stdio.h>
#include "unix_domain_socket_server.h"
#include "door_shared_memory/shared_packet_information.h"
#include "door_shared_memory/shared_memory.h"
#include "door_shared_memory/dpi.h"


int
main() {
    UnixDomainSocketServer socket = UnixDomainSocketServer();
    socket.run();

/*
    //read
    std::string key = "hoge";
    SharedMemory<Dpi, SharedPacketInformation>* sharedKeyMemory2 = new SharedMemory<Dpi, SharedPacketInformation>(key);
    Dpi* dpi2 = NULL;
    sharedKeyMemory2->read(&dpi2);
    std::cout << dpi2->data_ << std::endl;
    delete dpi2;
*/

    return 0;
};

