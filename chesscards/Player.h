#pragma once
#include "Deck.h"
#include "Hand.h"
#include "Graveyard.h"
#include "pstring.h"

enum SIDE
{
	NOSIDE,
	WHITE,
	BLACK,
};

class Player
{
	public:
		Player( pstring name, SIDE side, pstring deckpath );
		void Turn();
		pstring GetName() const { return m_name; }
		SIDE GetSide() const { return m_side; }

		Hand & GetHand() { return m_hand; }
		Deck & GetDeck() { return m_deck; }
		Graveyard & GetGraveyard() { return m_graveyard; }
	private:
		SIDE m_side;
		Deck m_deck;
		Hand m_hand;
		Graveyard m_graveyard;
		pstring m_name;
};