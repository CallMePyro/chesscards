#include "Deck.h"

vector<string> split_by_delim(const string & str, const char delim )
{
	vector<string> r;
	int idx = 0;
	r.push_back(string()); //start with empty string
	for each(auto c in str)
	{
		if (c != delim)
			r[idx] += c;
		else
		{
			r.push_back(string());
			idx++;
		}
	}
	return r;
}

Card::SPEC Deck::GetSpec(string & s)
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

PIECE Deck::GetPiece( string & s )
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

Deck::Deck( const string & filepath )
{
	//Load deck file as raw text
	string file((istreambuf_iterator<char>(ifstream(filepath))), istreambuf_iterator<char>());

	//Split deck file into lines
	vector<string> lines = split_by_delim(file, '\n');
	for each(auto line in lines)
	{
		//Split each line into seperate words, then determine their effective enum, and create/insert
		//a card into our vector
		vector<string> words = split_by_delim(line, ' ');

		PIECE pce = GetPiece( words[0] );
		Card::SPEC spec = GetSpec( words[1] );

		if( pce != NOPIECE && spec != Card::NOSPEC ) //dont put invalid cards into the deck
			m_cards.push_back( Card( pce, spec ) );
	}
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
	//using algorithm library. This is a much more reliable/faster shuffle than using rand
	unsigned seed = system_clock::now().time_since_epoch().count();
	shuffle( m_cards.begin(), m_cards.end(), default_random_engine( seed ) );
}

void Deck::AddCard(Card c)
{
	//normally I'd inline these but doing this for more readability
	m_cards.push_back(c);
}