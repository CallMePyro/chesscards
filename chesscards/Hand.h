#pragma once
#include "Card.h"
#include "Deck.h"
#include "Graveyard.h"
#include <vector>
	using std::vector;
#include "pstring.h"

#define STARTING_CARDS 5

class Hand
{
	public:
		Hand(Deck & d); //draw initial hand
		void Draw(Deck & d); //draw from a deck
		Card Play( int idx, Graveyard & g); //play card at idx, discard to graveyard
		pstring ToString() const; //used for displaying the hand
		vector<Card> GetCards() { return m_cards; }
	private:
		vector<Card> m_cards;
};