#include "Deck.h"

Card::SPEC Deck::GetSpec( pstring & s)
{
	//string to lowercase
	for (auto & a : s )
		a = tolower(a);

	//string to enum
	if (s == "n")
		return Card::N;
	else if (s == "ne")
		return Card::NE;
	else if (s == "e")
		return Card::E;
	else if (s == "se")
		return Card::SE;
	else if (s == "s")
		return Card::S;
	else if (s == "sw")
		return Card::SW;
	else if (s == "w")
		return Card::W;
	else if (s == "nw")
		return Card::NW;
	else
		return Card::NOSPEC;
}

PIECE Deck::GetPiece( pstring & s )
{
	//string to lowercase
	for( auto & a : s )
		a = tolower( a );

	//string to enum
	if( s == "pawn" )
		return PAWN;
	else if( s == "rook" )
		return ROOK;
	else if( s == "knight" )
		return KNIGHT;
	else if( s == "bishop" )
		return BISHOP;
	else if( s == "queen" )
		return QUEEN;
	else if( s == "king" )
		return KING;
	else
		return NOPIECE;
}

Deck::Deck( const pstring & filepath )
{
	pstring arg1, arg2;
	ifstream file( filepath.begin() ); //open file
	while( file >> arg1 >> arg2 ) //read each two chars
	{
		PIECE pce = GetPiece( arg1 );
		Card::SPEC spec = GetSpec( arg2 );

		if( pce != NOPIECE && spec != Card::NOSPEC ) //dont put invalid cards into the deck
			m_cards.push_back( Card( pce, spec ) );
	}
	file.close();
	Shuffle(); // shuffle dat
}

Card Deck::Draw()
{
	Card t = m_cards.back(); //cache last idx
	m_cards.pop_back(); //remove from array
	return t; //return cached card
}

void Deck::Shuffle()
{
	int i = 100;
	while( i-- )
	{
		int rand1 = rand() % m_cards.size();
		int rand2 = rand() % m_cards.size();

		Card t = m_cards[rand1];
		m_cards[rand1] = m_cards[rand2];
		m_cards[rand2] = t;
	}
}

void Deck::AddCard(Card c)
{
	//normally I'd inline these but doing this for more readability
	m_cards.push_back(c);
}