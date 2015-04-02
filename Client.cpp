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
    this->id = id;
    cout << prefix() << "Entering client constructor, id = " << id << endl;
    this->socket = socket;
    this->server = server;
    writing_mutex.lock();
    
    cout << prefix() << "Creating reading and listening threads." << endl;
    
    readingThread = new thread(&Client::_readingThread, this);
    writingThread = new thread(&Client::_writingThread, this);
    
    cout << prefix() << "Done creating threads." << endl;
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
            cout << prefix("reading thread") << "Client shut down connexion.";
            break;
        }
        if(res != -1)
        {
            cout << prefix() << "Received message: \"" << buf << "\"" << endl;
            char buf_free[1000];
            strcpy(buf_free, buf);
            execCmd(buf_free);
        }
    }
}

void Client::_writingThread()
{
    while(true)
    {
        writing_mutex.lock();
        for(char* msg : msgToWrite)
        {
            cout << prefix("writing thread") << "Trying to send following message \"" << msg 
                    << "\"" << endl;
            int res = send(socket, msg, strlen(msg), 0);
            if(res != -1)
            {
                cout << prefix() << "Message sent successfully." << endl;
            }
            else
            {
                perror(prefix("writing thread"));
            }
            delete msg;
        }
        msgToWrite.clear();
    }
}

const char* Client::prefix(const char* append)
{
    string ret = "[Client ";
    ret += to_string(id);
    if(append != NULL)
    {
        ret += " ";
        ret += append;
    }
    ret += "] ";
    return ret.c_str();
}

void Client::sendMsg(char* msg)
{
    cout << prefix("sendMsg") << "Sending following message: \"" << msg << "\""
            << endl;
    msgToWrite.push_back(msg);
    writing_mutex.unlock();
}

char* Client::extractCmd(char* msg)
{
    char*ret = NULL;
    if(msg[0] == '/' )
    {
        ret = strtok(msg, " ");
    }
    return ret;
}

void Client::sendCode(int code)
{
    char* str = new char[5];
    sprintf(str, "%d", code);
    msgToWrite.push_back(str);
    writing_mutex.unlock();
}

bool Client::checkChars(char* msg)
{
    for(int i=0; i < strlen(msg); i++)
    {
        char c = msg[i];
        bool valid = false;
        if(c >= '0' && c <= '9')
            valid = true;
        else if(c >= 'A' && c <= 'Z')
            valid = true;
        else if(c >= 'a' && c <= 'z')
            valid = true;
        if(!valid)
            return false;
    }
    return true;
}

void Client::talk(char* msg)
{
    server->talk(msg, this);
}


