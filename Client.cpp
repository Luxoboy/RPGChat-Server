/* 
 * File:   Client.cpp
 * Author: Anthony Correia <anthony.correia71@gmail.com>
 * 
 * Created on 18 mars 2015, 09:06
 */

#include "Client.h"
#include "Server.h"

#include <iostream>

using namespace std;

Client::Client(Server *server, int id, int socket)
{
    cout << "[CLIENT] Entering client constructor, id = " << id << endl;
    this->id = id;
    this->socket = socket;
    this->server = server;
    
    cout << prefix() << "Creating reading and listening threads." << endl;
}

Client::~Client()
{
}

void Client::_readingThread()
{
    
}

void Client::_writingThread()
{
    
}

char* Client::prefix()
{
    return "[Client " + id + "] ";
}

