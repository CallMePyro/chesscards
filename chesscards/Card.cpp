#include "Card.h"

Card::Card( PIECE p, Card::SPEC s ): m_piece( p ), m_spec( s )
{
}

inline pstring piece_tostring( PIECE p )
{
	switch( p )
	{
		case PAWN: return "Pawn to the ";
		case ROOK: return "Rook to the ";
		case KNIGHT: return "Knight to the ";
		case BISHOP: return "Bishop to the ";
		case QUEEN: return "Queen to the ";
		case KING: return "King to the ";
		case NOPIECE: return "Nopiece?";
		default: return "how did this happen";
	}
}

inline pstring spec_tostring( Card::SPEC s )
{
	switch( s )
	{
		case Card::N: return "North";
		case Card::NE: return "North-East";
		case Card::E: return "East";
		case Card::SE: return "South-East";
		case Card::S: return "South";
		case Card::SW: return "South-West";
		case Card::W: return "West";
		case Card::NW: return "North-West";
		default:
			cout << s;
			return "oh lord help something broke";
	}
}

pstring Card::ToString() const
{
	return piece_tostring( m_piece ) + spec_tostring( m_spec );
}