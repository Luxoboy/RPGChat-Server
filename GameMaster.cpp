/* 
 * File:   GameMaster.cpp
 * Author: Anthony Correia <anthony.correia71@gmail.com>
 * 
 * Created on 18 mars 2015, 09:06
 */

#include "GameMaster.h"
#include "Server.h"
#include "Client.h"

GameMaster::GameMaster(Server* server, int id, int socket)
: Client(server, id, socket)
{
}

GameMaster::GameMaster(const GameMaster& orig)
{
}

GameMaster::~GameMaster()
{
}

