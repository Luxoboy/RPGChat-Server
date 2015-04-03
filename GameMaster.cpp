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

#include "json/json.h"

#include <string>
#include <cstring>
#include <cstdlib>

using namespace std;
using namespace Json;

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
        if(server->isSetNbPlayers())
            ret = talk();
        else
            sendCode(MUST_SET_NB_PLAYERS);
    }
    else if(strcmp("/setnb", cmd) == 0)
    {
        arg1 = strtok(NULL, "\r");
        if(arg1 != NULL)
        {
            long nb = strtol(arg1, NULL, 0);
            if(nb != 0L && nb > 0)
            {
                server->setNbPlayers(nb);
                ret = true;
                sendCode(SUCCESS);
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
        else if(server->isPlaying())
            sendCode(GAME_HAS_ALREADY_STARTED);
        else if(server->getConnectedPlayers() < server->getNbPlayers())
            sendCode(NOT_ENOUGH_PLAYERS);
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
        if(server->isSetNbPlayers())
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
        else
            sendCode(MUST_SET_NB_PLAYERS);
    }
    else if(strcmp("/rand", cmd) == 0)
    {
        if(server->isPlaying())
        {
            arg1 = strtok(NULL, " ");
            arg2 = strtok(NULL, "\r");
            if(arg1 == NULL || arg2 == NULL)
                sendCode(MISSING_ARGUMENT);
            else
            {
                long min = strtol(arg1, NULL, 0),
                        max = strtol(arg2, NULL, 0);
                if(min != 0L && max != 0L && min < max)
                {
                    int res = (rand()%(max+min+1))+min;
                    Value answer;
                    answer["cmd"] = "rand";
                    answer["rand"] = res;
                    FastWriter writer;
                    string str = writer.write(answer);
                    char* str_c = new char[str.length()+1];
                    strcpy(str_c, str.c_str());
                    sendMsg(str_c);
                }
                else
                {
                    sendCode(INTERVAL_BOUNDS_INVALID);
                }
            }
        }
        else
            sendCode(GAME_HAS_NOT_STARTED);
    }
    else if(strcmp("/players", cmd) == 0)
    {
        if(server->isPlaying())
            ret = playersInfo();
        else
            sendCode(GAME_HAS_NOT_STARTED);
    }
    else if(strcmp("/lp", cmd) == 0)
    {
        if(!server->isPlaying())
            sendCode(GAME_HAS_NOT_STARTED);
        else
        {
            arg1 = strtok(NULL, " ");
            arg2 = strtok(NULL, " \r\n");
            ret = lp(arg1, arg2);
        }
    }
    delete msg;
    return ret;
}

bool GameMaster::lp(char* nicknames, char* mod)
{
    bool ret = false;
    if(nicknames == NULL || mod == NULL)
        sendCode(MISSING_ARGUMENT);
    else
    {
        vector<char*> v_nicknames;
        char* nname = strtok(nicknames, ",");
        while(nname != NULL)
        {
            v_nicknames.push_back(nname);
            nname = strtok(NULL, ",");
        }
        int mod_i = strtol(mod, NULL, 0);
        if(mod_i != 0L)
        {
            server->lp(v_nicknames, mod_i);
            if(v_nicknames.size() > 0)
                sendCode(NICKNAME_DOES_NOT_EXIST);
            else
            {
                ret = true;
                sendCode(SUCCESS);
            }
        }
        else
        {
            sendCode(MUST_BE_RELATIVE_INT);
        }
    }
    return ret;
}
