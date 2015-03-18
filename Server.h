/* 
 * File:   Server.h
 * Author: Anthony Correia <anthony.correia71@gmail.com>
 *
 * Created on 18 mars 2015, 09:05
 */

#ifndef SERVER_H
#define	SERVER_H

#define SERVER_PORT "4654"
#include <sys/socket.h> // Needed for the socket functions
#include <netdb.h>    


class Server
{
public:
    /**
     * Sets all the variables and creates the listening socket.
     * Sets the READY bool.
     */
    Server();
    virtual ~Server();
    
    /**
     * Tells wether the init (constructor) went well.
     * Should be called after constructor.
     * @return False if there was any error.
     */
    bool ready();
    
private:
    bool READY; //Indicates wether everything went well in construtor.
    int status; //Status variable
    int bind_socketfb; //Socket descriptor of listening socket.
    struct addrinfo host_info;       // The struct that getaddrinfo() fills up with data.
    struct addrinfo *host_info_list; // Pointer to the to the linked list of host_info's.
    
};

#endif	/* SERVER_H */

