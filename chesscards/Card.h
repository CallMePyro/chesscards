#pragma once
#include "pstring.h"

enum PIECE
{
	OOB, //Out of bounds
	NOPIECE,
	PAWN,
	ROOK,
	KNIGHT,
	BISHOP,
	QUEEN,
	KING,
};

class Card
{
	public:
		enum SPEC
		{
			NOSPEC,
			N,  //North
			NE, //North East
			E,  //East
			SE, //South East
			S,  //South
			SW, //South West
			W,  //West
			NW, //North West
		};

		Card( PIECE p = NOPIECE, SPEC s = Card::NOSPEC );
		pstring ToString() const;
		PIECE GetPiece() const { return m_piece; }
		SPEC GetSpec() const { return m_spec; }
	private:
		SPEC m_spec;
		PIECE m_piece;
};