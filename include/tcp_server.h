//
// Created by pepe on 20-11-22.
//

#ifndef PICO_REMOTE_CAR_TCP_SERVER_H
#define PICO_REMOTE_CAR_TCP_SERVER_H
#include <string.h>
#include <cstdlib>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "lwip/pbuf.h"
#include "lwip/tcp.h"

#define TCP_PORT 4242
#define BUF_SIZE 128
#define POLL_TIME_S 10



class TCPServer {
public:
    TCPServer();
    void init();
    err_t close();
    err_t get_result();
    err_t sent();
    err_t send_data();
    err_t receive_data();
    err_t poll();
    void error();
    err_t accept();
    bool open_connection();


private:
    struct tcp_pcb * server_pcb;
    struct tcp_pcb * client_pcb;
    bool complete;
    uint8_t buffer_sent[BUF_SIZE];
    uint8_t buffer_secv[BUF_SIZE];
    int sent_len;
    int recv_len;
    int run_count;

};

#endif //PICO_REMOTE_CAR_TCP_SERVER_H
