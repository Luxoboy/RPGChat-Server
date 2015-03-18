/* 
 * File:   Client.cpp
 * Author: Anthony Correia <anthony.correia71@gmail.com>
 * 
 * Created on 18 mars 2015, 09:06
 */

#include "Client.h"
#include "Server.h"

Client::Client(Server *server, int id, int socket)
{
    this->id = id;
    this->socket = socket;
    this->server = server;
}

Client::~Client()
{
}

