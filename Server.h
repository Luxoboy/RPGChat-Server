/* 
 * File:   Server.h
 * Author: Anthony Correia <anthony.correia71@gmail.com>
 *
 * Created on 18 mars 2015, 09:05
 */

#ifndef SERVER_H
#define	SERVER_H

#define SERVER_PORT "4654"

#include <sys/socket.h>
#include <netdb.h>    
#include <thread>
#include <mutex>
#include <vector>

class GameMaster;
class Player;

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
    
    /**
     * Starts the accepting thread. 
     * Should be called in order to allow players to connect to the server.
     * Should be called only when ready() returns true.
     * @return 
     */
    bool accept();
private:
    bool READY; //Indicates wether everything went well in construtor.
    bool ACCEPTING;
    int status; //Status variable
    int bind_socketfb; //Socket descriptor of listening socket.
    struct addrinfo host_info;       // The struct that getaddrinfo() fills up with data.
    struct addrinfo *host_info_list; // Pointer to the to the linked list of host_info's.
    std::thread *accepting_thread;
    std::mutex accepting_mutex;
    
    GameMaster* master; //Master of the game.
    std::vector<Player*> players; //Players of the game.
    
    void accept_thread();
};

#endif	/* SERVER_H */

