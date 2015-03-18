/* 
 * File:   Server.h
 * Author: Anthony Correia <anthony.correia71@gmail.com>
 *
 * Created on 18 mars 2015, 09:05
 */

#ifndef SERVER_H
#define	SERVER_H

#define SERVER_PORT 4654

#include <sys/socket.h> // Needed for the socket functions
#include <netdb.h>    


class Server
{
public:
    Server();
    virtual ~Server();
    
    bool ready();
private:
    bool READY;
    int status; //Status variable
    int bind_socketfb; //Socket descriptor of listening socket.
    struct addrinfo host_info;       // The struct that getaddrinfo() fills up with data.
    struct addrinfo *host_info_list; // Pointer to the to the linked list of host_info's.

};

#endif	/* SERVER_H */

