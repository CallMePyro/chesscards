#include "Graveyard.h"

//add a card to the graveyard
void Graveyard::AddCard(Card c)
{
	m_cards.push_back(c);
}

//return all the cards in a graveyard to the passed deck then empty self
void Graveyard::ReturnToDeck(Deck & deck)
{
	for each(auto card in m_cards)
		deck.AddCard(card);
	m_cards.empty();
}