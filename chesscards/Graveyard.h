#pragma once
#include "Card.h"
#include "Deck.h"
#include "pvector.h"
class Graveyard
{
	public:
		void ReturnToDeck(Deck & d); //puts all cards in a graveyard into the deck
		bool IsEmpty() { return !m_cards.size(); }
		void AddCard(Card c);
	private:
		pvector<Card> m_cards;
};