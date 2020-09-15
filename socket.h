#ifndef SOCHET_H
#define SOCHET_H

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <cstring>

#include "configure.h"

class Socket {

    int listenfd;
    int port;
    struct sockaddr_in serv_addr;

    public:
    explicit Socket(int port_): port(port_){};
    void set_listenfd();
    void set_sockaddr_in();
    int set_socket();

    int get_listenfd() const {return this->listenfd;};

};

#endif