#pragma once
#include "Card.h"
#include "Deck.h"
#include <vector>
	using std::vector;
class Graveyard
{
	public:
		Graveyard();
		void ReturnToDeck(Deck & d); //puts all cards in a graveyard into the deck
		bool IsEmpty() { return !m_cards.size(); }
		void AddCard(Card c);
	private:
		vector<Card> m_cards;
};