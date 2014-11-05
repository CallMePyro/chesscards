#pragma once
#include "Card.h"
#include <fstream>
	using std::ifstream;
#include <vector>
	using std::vector; //used for storing cards.

class Deck
{
	public:
		Deck( const pstring & deckpath );
		Card Draw();
		bool IsEmpty() { return !m_cards.size(); } //size is 0
		void Shuffle();
		void AddCard(Card c);
		static PIECE GetPiece( pstring & s);
		static Card::SPEC GetSpec( pstring & s);
	private:
		vector<Card> m_cards;
};