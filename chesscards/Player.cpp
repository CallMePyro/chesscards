#include "Player.h"

//yeah.
Player::Player( pstring name, SIDE side, pstring deckpath, bool ai ):m_name( name ), m_deck( deckpath.begin() ), m_hand( m_deck ), m_side( side ), m_ai( ai )
{
}