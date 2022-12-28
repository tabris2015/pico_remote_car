//
// Created by pepe on 20-11-22.
//
#include "tcp_server.h"

void TCPServer::init() {

}

bool TCPServer::open_connection() {
    printf("Starting server at %s on port %u\n", ip4addr_ntoa(netif_ip4_addr(netif_list)), TCP_PORT);
    struct tcp_pcb *pcb = tcp_new_ip_type(IPADDR_TYPE_ANY);
    if (!pcb) {
        printf("failed to create pcb\n");
        return false;
    }
    err_t err = tcp_bind(pcb, NULL, TCP_PORT);
    if (err) {
        printf("failed to bind to port %d\n");
        return false;
    }

    server_pcb = tcp_listen_with_backlog(pcb, 1);
    if (!server_pcb) {
        printf("failed to listen\n");
        if (pcb) {
            tcp_close(pcb);
        }
        return false;
    }

    tcp_arg(server_pcb, this);
    tcp_accept_fn accept_ptr = accept();
    tcp_accept(server_pcb, accept);

}
