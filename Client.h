/* 
 * File:   Client.h
 * Author: Anthony Correia <anthony.correia71@gmail.com>
 *
 * Created on 18 mars 2015, 09:06
 */

#ifndef CLIENT_H
#define	CLIENT_H

#include <thread>
#include <mutex>
#include <vector>
#include <string>

class Server;


class Client
{
public:
    Client(Server *server, int id, int socket);
    virtual ~Client();
    
    void sendMsg(std::string msg);
private:
    int id;
    int socket; //Socket between server and connected client
    Server *server;
    std::thread *readingThread, *writingThread;
    std::mutex writing_mutex;
    std::vector<std::string> msgToWrite;
    void _readingThread();
    void _writingThread();
    
    /**
     * Helper methods which returns output prefix. 
     * Exemple : [Client 1]
     * @return The string to be put at the begining of the output line.
     */
    virtual const char* prefix();
    
    
    
};

#endif	/* CLIENT_H */

