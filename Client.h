/* 
 * File:   Client.h
 * Author: Anthony Correia <anthony.correia71@gmail.com>
 *
 * Created on 18 mars 2015, 09:06
 */

#ifndef CLIENT_H
#define	CLIENT_H

class Server;


class Client
{
public:
    Client(Server *server, int id, int socket);
    virtual ~Client();
private:
    int id;
    int socket;
    Server *server;
};

#endif	/* CLIENT_H */

