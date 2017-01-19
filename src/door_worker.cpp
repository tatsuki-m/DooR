#include "door_worker.h"

//std::string BASE_SOCKET_DIR = "/tmp/unix-socket/";

DoorWorker::DoorWorker(std::string sharedDataKey, DoorSocketType type) : th_(&DoorWorker::run, this, sharedDataKey, type) {
}

DoorWorker::~DoorWorker() {
    std::cout << "DoorWorker::~DoorWorker" << std::endl;
    th_.join();
}

void
DoorWorker::run(std::string sharedDataKey, DoorSocketType type) {
    std::cout << "DoorWorker::run" << std::endl;
    type_ = type;
    sharedDataKey_ = sharedDataKey;
    switch(type) {
        case SHM:
            writeDataToShm();
            break;
        default:
            sendDataWithSocket();
            break;
    }
}

void
DoorWorker::writeDataToShm() {
    std::cout << "DoorWorker::writeDataToShm" << std::endl;
    SharedMemory<Dpi, SharedPacketInformation> doorShm = SharedMemory<Dpi, SharedPacketInformation>(sharedDataKey_);

    Dpi dpi = Dpi();
    for (int i =0; i < sizeof(dpi.data_); i++) {
        dpi.data_[i] = 'a';
    }

    std::cout << "DoorWorker::run start writing" << std::endl;
    doorShm.write(&dpi);
    doorShm.removeSharedMemory();
    std::cout << "DoorWorker::run finish writing" << std::endl;
}

void
DoorWorker::sendDataWithSocket() {
    //std::cout << "DoorWorker::sendDataWithSocket" << std::endl;
    //std::string socketName = BASE_SOCKET_DIR + sharedDataKey_;
    //SharedDataSocketServer socket = SharedDataSocketServer(socketName, type_);
    //socket.run();
    //unlink(socketName.c_str());
}

