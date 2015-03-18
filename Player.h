/* 
 * File:   Player.h
 * Author: Anthony Correia <anthony.correia71@gmail.com>
 *
 * Created on 18 mars 2015, 09:06
 */

#ifndef PLAYER_H
#define	PLAYER_H

#include "Client.h"


class Player : public Client
{
public:
    Player();
    Player(const Player& orig);
    virtual ~Player();
private:

};

#endif	/* PLAYER_H */

