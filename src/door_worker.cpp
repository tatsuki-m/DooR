#include "door_worker.h"

DoorWorker::DoorWorker(std::string shmKey) : th_(&DoorWorker::run, this, shmKey) {
}

DoorWorker::~DoorWorker() {
    std::cout << "DoorWorker::~DoorWorker" << std::endl;
    th_.join();
}

void
DoorWorker::run(std::string shmKey) {
    SharedMemory<Dpi, SharedPacketInformation> doorShm = SharedMemory<Dpi, SharedPacketInformation>(shmKey);
    std::cout << "DoorWorker::run" << std::endl;
    unsigned int id = 100;
    unsigned int srcPort = 1;
    unsigned int dstPort = 1;
    Dpi dpi = Dpi(id, srcPort, dstPort);
    std::cout << "DoorWorker::run start writing" << std::endl;
    doorShm.write(&dpi);
    std::cout << "DoorWorker::run finish writing" << std::endl;
}

