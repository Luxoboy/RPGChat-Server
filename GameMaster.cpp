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

#include "json.h"

#include <string>
#include <cstring>
#include <cstdlib>

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
    bool ret = false;
    char* cmd = extractCmd(msg);
    char *arg1, *arg2;
    if(strcmp(cmd, "/join") == 0)
    {
        sendCode(CANNOT_JOIN_IF_MASTER);
    }
    else if(strcmp("/talk", cmd) == 0)
    {
        ret = talk();
    }
    else if(strcmp("/setnb", cmd) == 0)
    {
        arg1 = strtok(NULL, "\r");
        if(arg1 != NULL)
        {
            long nb = strtol(arg1, NULL, 0);
            if(nb != 0L)
            {
                server->setNbPlayers(nb);
                ret = true;
            }
            else
                sendCode(NB_PLAYERS_MUST_BE_POSITIVE_INT);
        }
        else
            sendCode(NB_PLAYERS_MUST_BE_POSITIVE_INT);
    }
    else if(strcmp("/start", cmd) == 0)
    {
        if(!server->isSetNbPlayers())
            sendCode(MUST_SET_NB_PLAYERS);
        else if(server->getConnectedPlayers() < server->getNbPlayers())
            sendCode(NOT_ENOUGH_PLAYERS);
        else if(server->isPlaying())
            sendCode(GAME_HAS_ALREADY_STARTED);
        else
        {
            server->startGame();
            sendCode(SUCCESS);
        }
    }
    else if(strcmp("/end", cmd) == 0)
    {
        if(!server->isPlaying())
            sendCode(GAME_HAS_NOT_STARTED);
        else
        {
            server->endGame();
            sendCode(SUCCESS);
        }
    }
    else if(strcmp("/talkto", cmd) == 0)
    {
        arg1 = strtok(NULL, " ");
        arg2 = strtok(NULL, "\r");
        if(arg1 == NULL || arg2 == NULL)
            sendCode(MISSING_ARGUMENT);
        else
        {
            vector<char*> nicknames;
            char* nname = strtok(arg1, ",");
            while(nname != NULL)
            {
                nicknames.push_back(nname);
                nname = strtok(NULL, ",");
            }
            server->talkto(nicknames, arg2);
            if(nicknames.size() > 0)
                sendCode(NICKNAME_DOES_NOT_EXIST);
            else
                sendCode(SUCCESS);
        }
    }
    delete msg;
    return ret;
}



