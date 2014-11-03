#include "Hand.h"

Hand::Hand(Deck & deck)
{
	for (int i = 0; i < STARTING_CARDS; ++i)
		Draw(deck);
}

void Hand::Draw(Deck & deck)
{
	m_cards.push_back(deck.Draw()); //wheeew that was hard
}

Card Hand::Play( int idx, Graveyard & g )
{
	Card t = m_cards[idx]; //cache card
	m_cards.erase( m_cards.begin()+idx ); //delete card
	g.AddCard( t ); //add to graveyard
	return t; //return card to be effected on chessboard
}