#include "unix_domain_socket_server.h"

std::string BASE_SOCKET_NAME = "/tmp/unix-socket/door-unix-socket";
std::vector<DoorWorker*> UnixDomainSocketServer::doorWorkers;

void
signalHandler(int sigNum) {
    std::cout << "Interrupt signal (" << sigNum << ") received." << std::endl;
    unlink(BASE_SOCKET_NAME.c_str());
    UnixDomainSocketServer::deleteWorkers();
    std::cout << "Going to sleep.." <<std::endl;
    exit(sigNum);
}

// default  use for SHARED_SOCKET
UnixDomainSocketServer::UnixDomainSocketServer() {
    std::cout << "UnisDomainSocketServer: " << std::this_thread::get_id() << std::endl;
    socketName_ = BASE_SOCKET_NAME;
    unlink(socketName_.c_str());
}

UnixDomainSocketServer::~UnixDomainSocketServer() {
    closeSocket();
    deleteWorkers();
}


void
UnixDomainSocketServer::run() {
    signal(SIGINT, signalHandler);
    create();
    serve();
}

void
UnixDomainSocketServer::create() {
    try {
        struct sockaddr_un server_addr;
        int soval = 1;

        // setup socket address structure
        memset(&server_addr, 0, sizeof(server_addr));
        server_addr.sun_family = AF_UNIX;
        strncpy(server_addr.sun_path, socketName_.c_str(), sizeof(server_addr.sun_path) -1);

        // create socket
        server_ = socket(AF_UNIX, SOCK_STREAM, 0);
        if (!server_) {
            std::cerr << "UnisDomainSocketServer::Create socket: ";
            throw;
        }

        if (setsockopt(server_, SOL_SOCKET, SO_REUSEADDR, &soval, sizeof(soval)) == -1 ) {
            std::cerr << "UnisDomainSocketServer::Create setsockopt: ";
            throw;
        }

        // call bind to associate the socket with the UNIX file system
        if (bind(server_, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
            std::cerr << "UnisDomainSocketServer::Create bind: ";
            throw;
        }

        // convert the socket listen for incoming connections
        if (listen(server_, 10) < 0) {
            std::cerr << "UnisDomainSocketServer::Create listen: ";
            throw;
        }
    } catch(...) {
        closeSocket();
        deleteWorkers();
    }
}

void
UnixDomainSocketServer::serve() {
    int client;
    struct sockaddr_in client_addr;
    socklen_t clientlen = sizeof(client_addr);

    while (1) {
        std::cout << "socket running" << std::endl;
        try {
            if ((client = accept(server_, (struct sockaddr *)&client_addr, &clientlen)) > 0) {
                handle(client);
            } else {
                throw;
            }
        } catch(...) {
            closeSocket();
        }
    }
    closeSocket();
    deleteWorkers();
}

void
UnixDomainSocketServer::handle(int client) {
    bool is_success;
    SocketAck ack;
    if (is_success = getRequest(client, ack)) {
        switch(ack.type) {
            case ASK_DOOR:
                createDoorWorker(ack.data);
                sendAck(client, ack);
                break;
            default:
                break;
        }
    }
}

bool
UnixDomainSocketServer::getRequest(int client, SocketAck &ack) {
    std::cout << "UnixScoket::getRequest: " << std::endl;
    try {
        int cc;
        if ((cc=recv(client, &ack, sizeof(ack), 0)) > 0) {
            return true;
        } else {
            return false;
        }
    } catch(...) {
        closeSocket();
        deleteWorkers();
        return false;
    }
}

void
UnixDomainSocketServer::sendAck(int client, SocketAck &ack) {
    std::cout << "UnisDomainSocketServer::sendAck: " << std::endl;
    //ack.res = true;

    int cc;
    try {
        if ((cc = send(client, &ack, sizeof(ack), 0)) < 0) {
            std::cerr << "UnisDomainSocketServer::sendSocketName";
            throw;
        } else {
            std::cout << "UnixDomainDockerServer::sendAck() success" << std::endl;
        }
    } catch(...) {
        closeSocket();
        deleteWorkers();
    }

}

void
UnixDomainSocketServer::createDoorWorker(std::string shmKey) {
    DoorWorker *worker = new DoorWorker(shmKey);
    doorWorkers.push_back(worker);
}

void
UnixDomainSocketServer::closeSocket() {
    std::cout << "UnisDomainSocketServer::closeSocket()" << std::endl;
    unlink(socketName_.c_str());
}

void
UnixDomainSocketServer::deleteWorkers() {
    std::cout << "UnisDomainSocketServer::deleteWorkers()" << std::endl;
    std::for_each(doorWorkers.begin(), doorWorkers.end(), [](DoorWorker* p) { delete p; });
    doorWorkers.clear();
}

