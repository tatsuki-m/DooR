#ifndef DOOR_WORKER_H_
#define DOOR_WORKER_H_

#include <iostream>
#include <string>
#include <thread>

#include "door_shared_memory/shared_memory.h"
#include "door_shared_memory/shared_key.h"
#include "door_shared_memory/shared_packet_information.h"
#include "door_shared_memory/dpi.h"
#include "door_api/door_socket.h"

#include "shared_data_socket_server.h"

class DoorWorker
{
public:
    DoorWorker(std::string, DoorSocketType);
    ~DoorWorker();
private:
    void run(std::string, DoorSocketType);
    std::thread th_;
    DoorSocketType type_;
    std::string sharedDataKey_;
    void writeDataToShm();
    void sendDataWithSocket();
};

#endif

