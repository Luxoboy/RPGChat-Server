/* 
 * File:   Client.cpp
 * Author: Anthony Correia <anthony.correia71@gmail.com>
 * 
 * Created on 18 mars 2015, 09:06
 */

#include "Client.h"
#include "Server.h"

#include <unistd.h>
#include <iostream>
#include <string.h>
#include <sys/socket.h>

using namespace std;

Client::Client(Server *server, int id, int socket)
: writing_mutex()
{
    cout << "[CLIENT] Entering client constructor, id = " << id << endl;
    this->id = id;
    this->socket = socket;
    this->server = server;
    writing_mutex.lock();
    
    cout << prefix() << "Creating reading and listening threads." << endl;
    
    
}

Client::~Client()
{
}

void Client::_readingThread()
{
    char buf[1000];
    while(true)
    {
        int res = recv(socket, buf, 1000, MSG_DONTWAIT);
        if(res == 0)
        {
            cout << prefix() << "Client shut down connexion.";
            break;
        }
        if(res == -1)
        {
            perror(prefix());
            break;
        }
        char buf_free[1000];
        strcpy(buf, buf_free);
    }
}

void Client::_writingThread()
{
    while(true)
    {
        writing_mutex.unlock();
        for(string msg : msgToWrite)
        {
            cout << prefix() << "Trying to send following message \"" << msg 
                    << "\"" << endl;
            int res = send(socket, msg.c_str(), msg.size(), 0);
            if(res != -1)
            {
                cout << prefix() << "Message sent successfully." << endl;
            }
            else
            {
                perror(prefix());
            }
        }
    }
}

const char* Client::prefix()
{
    string ret = "[Client ";
    ret += id; 
    ret += "] ";
    return ret.c_str();
}

void Client::sendMsg(string msg)
{
    msgToWrite.push_back(msg);
    writing_mutex.unlock();
}