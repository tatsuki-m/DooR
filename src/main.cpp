#include <iostream>
#include <string>
#include <stdio.h>
#include "unix_domain_socket_server.h"

int
main() {
    UnixDomainSocketServer socket = UnixDomainSocketServer();
    socket.run();
};

