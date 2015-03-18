/* 
 * File:   GameMaster.h
 * Author: Anthony Correia <anthony.correia71@gmail.com>
 *
 * Created on 18 mars 2015, 09:06
 */

#ifndef GAMEMASTER_H
#define	GAMEMASTER_H

#include "Client.h"

class Server;
class GameMaster : public Client
{
public:
    GameMaster(Server* server, int id, int socket);
    virtual ~GameMaster();
private:

};

#endif	/* GAMEMASTER_H */

