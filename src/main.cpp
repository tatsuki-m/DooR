#include <iostream>
#include <string>
#include <stdio.h>
#include "unix_domain_socket_server.h"
#include "door_ipc/shared_packet_information.h"
#include "door_ipc/shared_memory.h"
#include "door_ipc/dpi.h"
#include "door_ipc/sync_semaphore.h"
#include "door_ipc/socket_client.h"


int
main() {
    UnixDomainSocketServer socket = UnixDomainSocketServer();
    socket.run();
/*
    SyncSemaphore sem;
    sem.create("hoge");
    sem.wait();
*/

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
*
/

/*
    int counter = 0;
    struct timespec startTime, endTime;
    //SharedMemory<Dpi, SharedPacketInformation> doorShm = SharedMemory<Dpi, SharedPacketInformation>(shmKey);
    clock_gettime(CLOCK_MONOTONIC, &startTime);
    while(counter<1000) {
        counter++;
    }
    clock_gettime(CLOCK_MONOTONIC, &endTime);
    std::string fileName = "hoge.csv";
    std::cout << fileName << std::endl;
    std::ofstream ofs(fileName.c_str(), std::ios::app);
    ofs << std::setfill('1') << std::setw(6) << startTime.tv_nsec << ",";
    ofs << std::setfill('0') << std::setw(6) << endTime.tv_nsec << ",";
    ofs << endTime.tv_nsec - startTime.tv_nsec << std::endl;
*/


    return 0;
};

