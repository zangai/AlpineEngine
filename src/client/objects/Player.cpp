#include "Player.hpp"

Player::Player(Resource *res, int charID) : Character(res)
{
    m_tile[0][0]->setTileset(0);
    m_tile[0][0]->setTile(charID*32);
    m_tile[0][1]->setTileset(0);
    m_tile[0][1]->setTile( 16 + ( charID*32 ) );
}

Player::~Player(void)
{
}
