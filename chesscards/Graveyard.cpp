#include "Graveyard.h"


Graveyard::Graveyard()
{
}

void Graveyard::AddCard(Card c)
{
	m_cards.push_back(c);
}

void Graveyard::ReturnToDeck(Deck & deck)
{
	for each(auto card in m_cards)
		deck.AddCard(card);
	m_cards.empty();
}