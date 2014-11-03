#pragma once
#include "Card.h"
#include <string>
	using std::string; //used for reading in file with stream iterators, 
					   //signifantly faster than with loops and cstrings
#include <fstream>
	using std::ifstream;
#include <streambuf>
	using std::istreambuf_iterator;
#include <vector>
	using std::vector; //used for storing cards.
#include <algorithm>
	using std::shuffle; //used for shuffling deck.
#include <random>
	using std::default_random_engine;
#include <chrono>
	using std::chrono::system_clock;

class Deck
{
	public:
		Deck( const string & deckpath );
		Card Draw();
		bool IsEmpty() { return !m_cards.size(); } //size is 0
		void Shuffle();
		void AddCard(Card c);
		PIECE GetPiece(string & s);
		Card::SPEC GetSpec(string & s);
	private:
		vector<Card> m_cards;
};

