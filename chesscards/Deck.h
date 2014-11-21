#pragma once
#include "Card.h"
#include <fstream>
	using std::ifstream;
#include "pvector.h"

class Deck
{
	public:
		Deck( const pstring & deckpath );
		Card Draw();
		bool IsEmpty() { return m_cards.empty(); }
		void Shuffle();
		void AddCard(Card c);
		static PIECE GetPiece( pstring & s);
		static Card::SPEC GetSpec( pstring & s);
	private:
		pvector<Card> m_cards;
};