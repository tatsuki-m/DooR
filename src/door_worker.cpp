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
    Dpi dpi = Dpi();
    for (int i =0; i < sizeof(dpi.data_); i++) {
        dpi.data_[i] = 'a';
    }

    std::cout << "DoorWorker::run start writing" << std::endl;
    doorShm.write(&dpi);
    doorShm.removeSharedMemory();
    std::cout << "DoorWorker::run finish writing" << std::endl;
}

