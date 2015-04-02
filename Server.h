/* 
 * File:   Server.h
 * Author: Anthony Correia <anthony.correia71@gmail.com>
 *
 * Created on 18 mars 2015, 09:05
 */

#ifndef SERVER_H
#define	SERVER_H

#define SERVER_PORT "4654"

#include <sys/socket.h>
#include <netdb.h>    
#include <thread>
#include <mutex>
#include <set>

#include "Player.h"


bool compareStr(const char* a, const char* b);


class GameMaster;
class Player;

class Server
{
public:
    /**
     * Sets all the variables and creates the listening socket.
     * Sets the READY bool.
     */
    Server();
    
    virtual ~Server();
    
    /**
     * Tells wether the init (constructor) went well.
     * Should be called after constructor.
     * @return False if there was any error.
     */
    bool ready();
    
    /**
     * Starts the accepting thread. 
     * Should be called in order to allow players to connect to the server.
     * Should be called only when ready() returns true.
     * @return 
     */
    bool accept();
    
    /**
     * Called by players when trying to join the game.
     * @param player The player who requested joining the game
     * @return 0 if successull, error code otherwise.
     */
    int joinGame(Player* player);
    
    /**
     * Send a message to all players, except sender.
     * @param except The client who sent the message
     * @param msg The message to be sent.
     */
    void talk(char* msg, Client* except);
    
    /**
     * Send a message to selected players.
     * Players are chosen with their nicknames (case insensitive).
     * Should only be called by game master.
     * @param nicknames
     * @param msg
     */
    void talkto(std::vector<char*> &nicknames, char* msg);
    
    /**
     * Tells wether a player has already joined the game.
     * @param p Player to check.
     * @return True if the player has already joined.
     */
    bool hasJoined(Player* p);
    
    /**
     * Tells wether the chosen nickname is available.
     * @param nickname Chosen nickname
     * @return True if nickname is available.
     */
    bool isNicknameAvailable(char* nickname);
    
    /**
     * Starts the game.
     */
    void startGame();
    
    /**
     * Ends game.
     */
    void endGame();
    
    /**
     * Tells wether required number of players was set by master.
     * @return 
     */
    bool isSetNbPlayers();
    
    /**
     * Sets the required number of players for the game to start.
     * @param nb
     */
    void setNbPlayers(int nb);
    
    /**
     * Required number of players for the game to start.
     * @return 
     */
    int getNbPlayers();
    
    /**
     * Number of players who have joined the game.
     * @return 
     */
    int getConnectedPlayers();
    
    /**
     * Tells if the game has started and is running.
     * @return True if running.
     */
    bool isPlaying();
    
private:
    
    
    void accept_thread();
    
    static void toLower(char* str);
    
    bool READY; //Indicates wether everything went well in construtor.
    bool ACCEPTING;
    bool PLAYING; //Indicates if the game has started.
    int NB_PLAYERS;
    int status; //Status variable
    int bind_socketfb; //Socket descriptor of listening socket.
    int player_ids; //Incremented id for players.
    struct addrinfo host_info;       // The struct that getaddrinfo() fills up with data.
    struct addrinfo *host_info_list; // Pointer to the to the linked list of host_info's.
    std::thread *accepting_thread;
    std::mutex accepting_mutex;
    
    GameMaster* master; //Master of the game.
    std::set<Player*> players; //Players who have joined the game.
    std::set<Player*> connected_players; //Connected players who haven't joined.
};

#endif	/* SERVER_H */

