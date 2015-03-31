/* 
 * File:   GameMaster.cpp
 * Author: Anthony Correia <anthony.correia71@gmail.com>
 * 
 * Created on 18 mars 2015, 09:06
 */

#include "GameMaster.h"
#include "Server.h"
#include "Client.h"
#include "errcodes.h"

#include <string>

using namespace std;

GameMaster::GameMaster(Server* server, int id, int socket)
: Client(server, id, socket)
{
    sendCode(YOU_ARE_GAMEMASTER);
}


GameMaster::~GameMaster()
{
}

const char* GameMaster::prefix(const char* append)
{
    string s = "[GameMaster";
    if(append != NULL)
    {
        s+=" ";
        s += append;
    }
    s += "] ";
    return s.c_str();
}

bool GameMaster::execCmd(char* msg)
{
    return true;
}



