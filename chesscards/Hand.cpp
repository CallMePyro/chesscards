#include "Hand.h"

//initial constructor for hand, pass a deck for initial draw
Hand::Hand(Deck & deck)
{
	for( int i = 0; i < STARTING_CARDS; ++i )
		Draw( deck );
}

//draw a card from the passed deck
void Hand::Draw( Deck & deck )
{
	m_cards.push_back(deck.Draw()); //wheeew that was hard
}

//play a card to a graveyard and return it
Card Hand::Play( int idx, Graveyard & g )
{
	Card t = m_cards[idx]; //cache card
	m_cards.remove( idx ); //delete card
	g.AddCard( t ); //add to graveyard
	return t; //return card to be effected on chessboard
}