/* 
 * File:   Player.cpp
 * Author: Anthony Correia <anthony.correia71@gmail.com>
 * 
 * Created on 18 mars 2015, 09:06
 */

#include "Player.h"
#include "Server.h"
#include "Client.h"
#include "errcodes.h"

#include "json/json.h"

#include <cstring>

using namespace std;

Player::Player(Server* server, int id, int socket)
: Client(server, id, socket)
{
    lifePoints = LP_START;
    sendCode(WELCOME);
}

Player::~Player()
{
}

bool Player::execCmd(char* msg)
{
    bool ret = false;
    char* cmd = extractCmd(msg);
    char *arg1, *arg2;
    if(cmd == NULL)
    {
        ret = false;
        sendCode(INVALID_COMMAND);
    }
    else if(strcmp(cmd, "/join") == 0)
    {
        if(server->isSetNbPlayers())
        {
            if(server->hasJoined(this))
                sendCode(YOU_ALREADY_JOINED);
            else if(server->getConnectedPlayers() >= server->getNbPlayers())
                sendCode(NO_SLOT_AVAILABLE);
            else
                ret = join(strtok(NULL, "\r"));
        }
        else
            sendCode(MASTER_HAS_NOT_SET_NB_PLAYERS);
    }
    else if(strcmp("/talk", cmd) == 0)
    {
        if(server->hasJoined(this))
            if(server->isPlaying())
                ret = talk();
            else
                sendCode(GAME_HAS_NOT_STARTED);
        else
            sendCode(YOU_ARE_NOT_PLAYING);
    }
    else if(strcmp("/players", cmd) == 0)
    {
        if(server->hasJoined(this))
        {
            if(server->isPlaying())
            {
                if(server->getNbPlayers() > 1)
                    ret = playersInfo();
                else
                    sendCode(YOU_ARE_THE_ONLY_PLAYER);
            }
            else
                sendCode(GAME_HAS_NOT_STARTED);
        }
        else
            sendCode(YOU_ARE_NOT_PLAYING);
    }
    else if(strcmp("/lp", cmd) == 0)
    {
        ret = lp();
    }
    else
        sendCode(INVALID_COMMAND);

    delete msg;
    return ret;
}

bool Player::join(char* nickname)
{
    bool ret = false;
    if(nickname == NULL)
        sendCode(YOU_MUST_CHOOSE_A_NICKNAME);
    else if(!checkChars(nickname))
    {
        sendCode(NICKNAME_NOT_VALID);
    }
    else
    {
        if(!server->isNicknameAvailable(nickname))
        {
            sendCode(NICKNAME_ALREADY_USED);
        }
        else
        {
            ret = true;
            strcpy(this->nickname, nickname);
            server->joinGame(this);
            sendCode(SUCCESS);
        }
    }
    return ret;
}

char* Player::getNickname() const
{
    char* copy = new char[strlen(nickname)+1];
    strcpy(copy, nickname);
    return copy;
}

int Player::getLifePoint()
{
    return lifePoints;
}

bool Player::lp(char* nicknames, char* mod)
{
    bool ret = false;
    if(server->hasJoined(this))
    {
        if(!server->isPlaying())
            sendCode(GAME_HAS_NOT_STARTED);
        else
        {
            Json::Value root;
            root["cmd"] = "lp";
            root["alive"] = lifePoints > 0;
            root["lp"] = lifePoints;
            Json::FastWriter wr;
            string str = wr.write(root);
            char* msg = new char[str.length()+1];
            strcpy(msg, str.c_str());
            sendMsg(msg);
            ret = true;
        }
    }
    else
        sendCode(YOU_ARE_NOT_PLAYING);
    return ret;
}

void Player::editLifePoint(int mod)
{
    if(lifePoints > 0)
        lifePoints+=mod;
}

bool Player::isAlive()
{
    return lifePoints > 0;
}

void Player::reset()
{
    lifePoints = LP_START;
}
