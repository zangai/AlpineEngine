#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include "Resource.hpp"
#include "character.hpp"

class Player : public Character
{
    public:
        Player(Resource *res, int charId);
        ~Player(void);
    private:
        int m_charId;
};

#endif _PLAYER_HPP_
