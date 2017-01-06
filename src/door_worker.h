#ifndef DOOR_WORKER_H_
#define DOOR_WORKER_H_

#include <iostream>
#include <string>
#include <thread>

#include "door_shared_memory/shared_memory.h"
#include "door_shared_memory/shared_packet_information.h"
#include "door_shared_memory/dpi.h"

class DoorWorker
{
public:
    DoorWorker(std::string);
    ~DoorWorker();
private:
    void run(std::string);
    std::thread th_;
};

#endif

