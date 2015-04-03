/* 
 * File:   Player.h
 * Author: Anthony Correia <anthony.correia71@gmail.com>
 *
 * Created on 18 mars 2015, 09:06
 */

#ifndef PLAYER_H
#define	PLAYER_H

#define LP_START 10

#include "Client.h"

class Server;

class Player : public Client
{
public:
    Player(Server* server, int id, int socket);
    virtual ~Player();
    
    /**
     * Returns new allocated string to nickname.
     * Returned string should be deleted from memory.
     * @return Newly allocated string pointing to player's nickname.
     */
    char* getNickname() const;
    
    int getLifePoint();
    
    /**
     * Edits life points of player.
     * @param mod Modifier (positive or negative).
     */
    void editLifePoint(int mod);
    
    /**
     * Tells wether the player is alive.
     * @return 
     */
    bool isAlive();
    
    /**
     * Called after the game is finished, resets the life points.
     */
    void reset();
private:
    char nickname[11]; //Nickname displayed to other players. Set when joining.
    int lifePoints;

    virtual bool execCmd(char* msg);
    
    bool join(char* nickname);
    

    virtual bool lp(char* nicknames = NULL, char* mod = NULL);

};

#endif	/* PLAYER_H */

