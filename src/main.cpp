#include <iostream>
#include <string>
#include <stdio.h>
#include "unix_domain_socket_server.h"
#include "door_ipc/shared_packet_information.h"
#include "door_ipc/shared_memory.h"
#include "door_ipc/dpi.h"


int
main() {
    UnixDomainSocketServer socket = UnixDomainSocketServer();
    socket.run();
/*
    //read
    std::string key = "hoge";
    SharedMemory<Dpi, SharedPacketInformation> sharedKeyMemory2 = SharedMemory<Dpi, SharedPacketInformation>(key);
    Dpi dpi = Dpi();
    for (unsigned long i = 0; i < SharedPacketInformation::getSharedDataSize(); i++) {
        dpi.data_[i] = 'a';
    }
    sharedKeyMemory2.write(&dpi);
    sharedKeyMemory2.removeSharedMemory();
*/

    return 0;
};

