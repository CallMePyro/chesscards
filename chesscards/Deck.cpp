#include "Deck.h"

//turn a string in a card spec
Card::SPEC Deck::GetSpec( pstring & s )
{
	//string to lowercase
	for( auto & a : s )
		a = tolower( a );

	//string to enum
	if( s == "n" )
		return Card::N;
	else if( s == "ne" )
		return Card::NE;
	else if( s == "e" )
		return Card::E;
	else if( s == "se" )
		return Card::SE;
	else if( s == "s" )
		return Card::S;
	else if( s == "sw" )
		return Card::SW;
	else if( s == "w" )
		return Card::W;
	else if( s == "nw" )
		return Card::NW;
	else
		return Card::NOSPEC;
}

//turn a string into a card piece
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

//intitial constructor for deck, pass a fileapth to read the deck from
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

//just pass a card back and remove it from the top of the deck
Card Deck::Draw()
{
	return m_cards.pop_back(); //remove from array and return card removed
}

//shuffle a deck
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

//add the passed card to the deck
void Deck::AddCard( Card c )
{
	//normally I'd inline these but doing this for more readability
	m_cards.push_back( c );
}