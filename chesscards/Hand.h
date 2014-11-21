#pragma once
#include "Card.h"
#include "Deck.h"
#include "Graveyard.h"
#include "pvector.h"
#include "pstring.h"

#define STARTING_CARDS 7

class Hand
{
	public:
		Hand(Deck & d); //draw initial hand
		void Draw(Deck & d); //draw from a deck
		Card Play( int idx, Graveyard & g); //play card at idx, discard to graveyard
		pstring ToString() const; //used for displaying the hand
		pvector<Card> GetCards() { return m_cards; }
	private:
		pvector<Card> m_cards;
};