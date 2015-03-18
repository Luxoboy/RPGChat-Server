/* 
 * File:   Server.cpp
 * Author: Anthony Correia <anthony.correia71@gmail.com>
 * 
 * Created on 18 mars 2015, 09:05
 */

#include "Server.h"

#include <iostream>
#include <string.h>
#include <cstdio>
#include <thread>

using namespace std;

Server::Server()
{
    cout << "[SERVER] Entering Server constructor." << endl <<
            "[SERVER] Init variables." << endl;
    
    
    READY = false;
    ACCEPTING = false;
    accepting_thread = NULL;
    
    memset(&host_info, 0, sizeof host_info);
    host_info.ai_family = AF_UNSPEC;
    host_info.ai_socktype = SOCK_STREAM;
    host_info.ai_flags = AI_PASSIVE;
    
    status = getaddrinfo(NULL, SERVER_PORT, &host_info, &host_info_list);
    
    if (status != 0)  
    {
        cout << "getaddrinfo error" << gai_strerror(status) ;
        return;
    }
    
    cout << "Creating the listening socket"  << std::endl;
    bind_socketfb = socket(host_info_list->ai_family, host_info_list->ai_socktype | SOCK_NONBLOCK,
                      host_info_list->ai_protocol);
    if (bind_socketfb == -1)  
    {
        perror("[SERVER] Creating listening socket");
        return;
    }

    cout << "Binding socket..."  << std::endl;
    int yes = 1;
    status = setsockopt(bind_socketfb, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
    if(status == -1)
    {
        perror("[SERVER] setsockopt");
        return;
    }
    status = bind(bind_socketfb, host_info_list->ai_addr, host_info_list->ai_addrlen);
    if (status == -1)  
    {
        perror("[SERVER] bind");
        return;
    }

    std::cout << "Setting socket as a listening socket..."  << std::endl;
    status =  listen(bind_socketfb, 5);
    if (status == -1)  
    {
        std::cout << "listen error" << std::endl ;
        return;
    }
    READY = true;
    cout << "[SERVER] All done, server ready." << endl;
}

Server::~Server()
{
    if(status != -1)
    {
        
    }
}

bool Server::ready()
{
    return READY;
}

bool Server::accept()
{
    bool ret;
    if(READY == false)
    {
        cout << "[SERVER] Cannot start accepting clients, server is not ready!" <<
                endl;
        ret = false;
    }
    else
    {
        ACCEPTING = true;
        accepting_thread = new thread(&Server::accept_thread, this);
        accepting_thread->join();
    }
    
    return ret;
}

void Server::accept_thread()
{
    struct sockaddr_storage their_addr;
    socklen_t addr_size = sizeof(their_addr);
    while(true)
    {
        accepting_mutex.lock();
        if(ACCEPTING)
        {
            int new_socket = accept4(bind_socketfb, (struct sockaddr *)&their_addr, 
                    &addr_size, SOCK_NONBLOCK);
            cout << "[SERVER] Accepting loop" << endl;
        }
        accepting_mutex.unlock();
    }
    
    
}
