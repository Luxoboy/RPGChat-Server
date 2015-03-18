/* 
 * File:   Player.cpp
 * Author: Anthony Correia <anthony.correia71@gmail.com>
 * 
 * Created on 18 mars 2015, 09:06
 */

#include "Player.h"
#include "Server.h"
#include "Client.h"

Player::Player(Server* server, int id, int socket)
: Client(server, id, socket)
{
}

Player::Player(const Player& orig)
{
}

Player::~Player()
{
}

