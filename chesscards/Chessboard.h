#pragma once
#include "Card.h"
#include "Player.h"
#include <string>
	using std::string;
#include <iostream>
	using std::cout;
	using std::cin;
#include <Windows.h>

struct Piece //'Piece' barely looks like a word anymore
{
	PIECE type;
	SIDE side;
	Piece( PIECE t = PIECE::NOPIECE, SIDE s = SIDE::NOSIDE ):type( t ), side( s ) {} //default constructor
};

class Chessboard
{
	public:
		Chessboard();

		void Move( Player & ply );
		void MoveHuman( Player & ply );
		void MoveAI( Player & ply );
		bool GameOver() const { return m_end; }
		pstring ToString( SIDE s ) const;

		bool IsValidMove( SIDE side, const Card & c ) const;

		PIECE PieceMoveResult( short row, short column, short dist, Card::SPEC dir ) const;
		PIECE CanMovePawn    ( short row, short column, short dist, Card::SPEC dir ) const;
		PIECE CanMoveRook    ( short row, short column, short dist, Card::SPEC dir ) const;
		PIECE CanMoveKnight  ( short row, short column,             Card::SPEC dir ) const;
		PIECE CanMoveBishop  ( short row, short column, short dist, Card::SPEC dir ) const;
		PIECE CanMoveQueen   ( short row, short column, short dist, Card::SPEC dir ) const;

		void MovePiece ( short row, short column, short dist, Card::SPEC dir ); //determines which move function to use
		void MovePawn  ( short row, short column, short dist, Card::SPEC dir );
		void MoveRook  ( short row, short column, short dist, Card::SPEC dir );
		void MoveKnight( short row, short column,             Card::SPEC dir );
		void MoveBishop( short row, short column, short dist, Card::SPEC dir );
		void MoveQueen ( short row, short column, short dist, Card::SPEC dir ); //king will just pass 1 for the dist

		short RookMoveDistance  ( short row, short column, Card::SPEC dir ) const;
		short BishopMoveDistance( short row, short column, Card::SPEC dir ) const;
		short QueenMoveDistance ( short row, short column, Card::SPEC dir ) const;

		short * GetPiece( const Card & c, SIDE side ) const;
		short GetPieceMaxDist( short row, short column, Card::SPEC dir ) const;
		short GetDistance( short row, short column, Card::SPEC dir ) const;

	private:
		Piece m_array [8][8];
		bool m_end = false;
};