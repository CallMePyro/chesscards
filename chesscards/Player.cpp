#include "Player.h"


Player::Player(pstring name, SIDE side, pstring deckpath):m_name(name), m_deck(deckpath.begin()), m_hand(m_deck), m_side(side)
{
}

void Player::Turn()
{

}