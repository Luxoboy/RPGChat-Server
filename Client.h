/* 
 * File:   Client.h
 * Author: Anthony Correia <anthony.correia71@gmail.com>
 *
 * Created on 18 mars 2015, 09:06
 */

#ifndef CLIENT_H
#define	CLIENT_H

#include <thread>
#include <mutex>
#include <vector>
#include <string>

class Server;


class Client
{
public:
    Client(Server *server, int id, int socket);
    virtual ~Client();
    
    void sendMsg(char* msg);
    
    /**
     * Send error code to client.
     * @param code The error code, as described in protocol.
     */
    void sendCode(int code);
protected:
    int id;
    int socket; //Socket between server and connected client
    Server *server;
    std::thread *readingThread, *writingThread;
    std::mutex writing_mutex; //Mutex to trigger writing thread to actually send messages.
    std::mutex msgToWrite_mutex; //Mutex to protect access to messages vector.
    std::vector<char*> msgToWrite;
    void _readingThread();
    void _writingThread();
    
    /**
     * Helper methods which returns output prefix. 
     * Exemple : [Client 1]
     * @return The string to be put at the begining of the output line.
     */
    virtual const char* prefix(const char* append = NULL);

    /**
     * Executes a command.
     * @param cmd The received command
     * @return True if the command is valid.
     */
    virtual bool execCmd(char* msg) =0;
    

    /**
     * Extracts the command from a received string.
     * @param cmd The received string with command and arguments
     * @return cmd if string is valid, NULL otherwise.
     */
    char* extractCmd(char* msg);
    
    /**
     * Check if a string contains only letters and numbers.
     * @param msg The string to check
     * @return True if string is valid, false otherwise.
     */
    static bool checkChars(char* msg);
    
    /**
     * Talks to every other players.
     * Message is transmitted to server who broadcasts the message.
     * @param msg Message to be sent.
     * @return True if mesage is correct and was successfully sent.
     */
    bool talk();
};

#endif	/* CLIENT_H */

